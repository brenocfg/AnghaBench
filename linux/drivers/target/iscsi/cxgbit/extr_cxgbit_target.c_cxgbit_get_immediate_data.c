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
struct iscsi_scsi_req {int /*<<< orphan*/  cmdsn; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_state; scalar_t__ unsolicited_data; int /*<<< orphan*/  se_cmd; scalar_t__ sense_reason; int /*<<< orphan*/  first_burst_len; struct iscsi_conn* conn; } ;

/* Variables and functions */
 int CMDSN_ERROR_CANNOT_RECOVER ; 
 int CMDSN_LOWER_THAN_EXP ; 
 int IMMEDIATE_DATA_ERL1_CRC_FAILURE ; 
 int IMMEDIATE_DATA_NORMAL_OPERATION ; 
 int /*<<< orphan*/  ISTATE_REMOVE ; 
 int cxgbit_handle_immediate_data (struct iscsi_cmd*,struct iscsi_scsi_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_sequence_cmd (struct iscsi_conn*,struct iscsi_cmd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_set_unsolicited_dataout (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  target_put_sess_cmd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cxgbit_get_immediate_data(struct iscsi_cmd *cmd, struct iscsi_scsi_req *hdr,
			  bool dump_payload)
{
	struct iscsi_conn *conn = cmd->conn;
	int cmdsn_ret = 0, immed_ret = IMMEDIATE_DATA_NORMAL_OPERATION;
	/*
	 * Special case for Unsupported SAM WRITE Opcodes and ImmediateData=Yes.
	 */
	if (dump_payload)
		goto after_immediate_data;

	immed_ret = cxgbit_handle_immediate_data(cmd, hdr,
						 cmd->first_burst_len);
after_immediate_data:
	if (immed_ret == IMMEDIATE_DATA_NORMAL_OPERATION) {
		/*
		 * A PDU/CmdSN carrying Immediate Data passed
		 * DataCRC, check against ExpCmdSN/MaxCmdSN if
		 * Immediate Bit is not set.
		 */
		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
						(unsigned char *)hdr,
						hdr->cmdsn);
		if (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			return -1;

		if (cmd->sense_reason || cmdsn_ret == CMDSN_LOWER_THAN_EXP) {
			target_put_sess_cmd(&cmd->se_cmd);
			return 0;
		} else if (cmd->unsolicited_data) {
			iscsit_set_unsolicited_dataout(cmd);
		}

	} else if (immed_ret == IMMEDIATE_DATA_ERL1_CRC_FAILURE) {
		/*
		 * Immediate Data failed DataCRC and ERL>=1,
		 * silently drop this PDU and let the initiator
		 * plug the CmdSN gap.
		 *
		 * FIXME: Send Unsolicited NOPIN with reserved
		 * TTT here to help the initiator figure out
		 * the missing CmdSN, although they should be
		 * intelligent enough to determine the missing
		 * CmdSN and issue a retry to plug the sequence.
		 */
		cmd->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, conn, cmd->i_state);
	} else /* immed_ret == IMMEDIATE_DATA_CANNOT_RECOVER */
		return -1;

	return 0;
}