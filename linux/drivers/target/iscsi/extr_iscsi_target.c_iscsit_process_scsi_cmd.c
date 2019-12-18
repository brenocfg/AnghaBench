#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iscsi_scsi_req {int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  cmdsn; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {scalar_t__ sense_reason; int /*<<< orphan*/  se_cmd; scalar_t__ unsolicited_data; int /*<<< orphan*/  immediate_data; } ;

/* Variables and functions */
 int CMDSN_ERROR_CANNOT_RECOVER ; 
 int CMDSN_LOWER_THAN_EXP ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_ack_from_expstatsn (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_sequence_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_set_unsolicited_dataout (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  target_put_sess_cmd (int /*<<< orphan*/ *) ; 
 scalar_t__ transport_generic_new_cmd (int /*<<< orphan*/ *) ; 

int iscsit_process_scsi_cmd(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
			    struct iscsi_scsi_req *hdr)
{
	int cmdsn_ret = 0;
	/*
	 * Check the CmdSN against ExpCmdSN/MaxCmdSN here if
	 * the Immediate Bit is not set, and no Immediate
	 * Data is attached.
	 *
	 * A PDU/CmdSN carrying Immediate Data can only
	 * be processed after the DataCRC has passed.
	 * If the DataCRC fails, the CmdSN MUST NOT
	 * be acknowledged. (See below)
	 */
	if (!cmd->immediate_data) {
		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
					(unsigned char *)hdr, hdr->cmdsn);
		if (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			return -1;
		else if (cmdsn_ret == CMDSN_LOWER_THAN_EXP) {
			target_put_sess_cmd(&cmd->se_cmd);
			return 0;
		}
	}

	iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

	/*
	 * If no Immediate Data is attached, it's OK to return now.
	 */
	if (!cmd->immediate_data) {
		if (!cmd->sense_reason && cmd->unsolicited_data)
			iscsit_set_unsolicited_dataout(cmd);
		if (!cmd->sense_reason)
			return 0;

		target_put_sess_cmd(&cmd->se_cmd);
		return 0;
	}

	/*
	 * Early CHECK_CONDITIONs with ImmediateData never make it to command
	 * execution.  These exceptions are processed in CmdSN order using
	 * iscsit_check_received_cmdsn() in iscsit_get_immediate_data() below.
	 */
	if (cmd->sense_reason)
		return 1;
	/*
	 * Call directly into transport_generic_new_cmd() to perform
	 * the backend memory allocation.
	 */
	cmd->sense_reason = transport_generic_new_cmd(&cmd->se_cmd);
	if (cmd->sense_reason)
		return 1;

	return 0;
}