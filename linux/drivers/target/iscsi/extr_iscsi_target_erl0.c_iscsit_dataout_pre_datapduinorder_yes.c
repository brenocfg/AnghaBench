#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_seq {scalar_t__ offset; } ;
struct iscsi_data {int /*<<< orphan*/  offset; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {scalar_t__ write_data_done; int /*<<< orphan*/  init_task_tag; struct iscsi_seq* seq_ptr; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ErrorRecoveryLevel; scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ iscsit_dump_data_payload (struct iscsi_conn*,int /*<<< orphan*/ ,int) ; 
 int iscsit_recover_dataout_sequence (struct iscsi_cmd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int iscsit_dataout_pre_datapduinorder_yes(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	int dump = 0, recovery = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * For DataSequenceInOrder=Yes: If the offset is greater than the global
	 * DataPDUInOrder=Yes offset counter in struct iscsi_cmd a protcol error has
	 * occurred and fail the connection.
	 *
	 * For DataSequenceInOrder=No: If the offset is greater than the per
	 * sequence DataPDUInOrder=Yes offset counter in struct iscsi_seq a protocol
	 * error has occurred and fail the connection.
	 */
	if (conn->sess->sess_ops->DataSequenceInOrder) {
		if (be32_to_cpu(hdr->offset) != cmd->write_data_done) {
			pr_err("Command ITT: 0x%08x, received offset"
			" %u different than expected %u.\n", cmd->init_task_tag,
				be32_to_cpu(hdr->offset), cmd->write_data_done);
			recovery = 1;
			goto recover;
		}
	} else {
		struct iscsi_seq *seq = cmd->seq_ptr;

		if (be32_to_cpu(hdr->offset) > seq->offset) {
			pr_err("Command ITT: 0x%08x, received offset"
			" %u greater than expected %u.\n", cmd->init_task_tag,
				be32_to_cpu(hdr->offset), seq->offset);
			recovery = 1;
			goto recover;
		} else if (be32_to_cpu(hdr->offset) < seq->offset) {
			pr_err("Command ITT: 0x%08x, received offset"
			" %u less than expected %u, discarding payload.\n",
				cmd->init_task_tag, be32_to_cpu(hdr->offset),
				seq->offset);
			dump = 1;
			goto dump;
		}
	}

	return DATAOUT_NORMAL;

recover:
	if (!conn->sess->sess_ops->ErrorRecoveryLevel) {
		pr_err("Unable to perform within-command recovery"
				" while ERL=0.\n");
		return DATAOUT_CANNOT_RECOVER;
	}
dump:
	if (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
		return DATAOUT_CANNOT_RECOVER;

	return (recovery) ? iscsit_recover_dataout_sequence(cmd,
		be32_to_cpu(hdr->offset), payload_length) :
	       (dump) ? DATAOUT_WITHIN_COMMAND_RECOVERY : DATAOUT_NORMAL;
}