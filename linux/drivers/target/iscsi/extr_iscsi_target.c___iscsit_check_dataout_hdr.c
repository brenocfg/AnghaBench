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
typedef  scalar_t__ u32 ;
struct se_cmd {scalar_t__ data_length; scalar_t__ t_state; int se_cmd_flags; int transport_state; } ;
struct iscsi_data {int flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  datasn; int /*<<< orphan*/  ttt; int /*<<< orphan*/  itt; } ;
struct iscsi_conn {TYPE_2__* sess; int /*<<< orphan*/  cid; } ;
struct iscsi_cmd {int cmd_flags; scalar_t__ data_direction; int outstanding_r2ts; struct se_cmd se_cmd; scalar_t__ unsolicited_data; int /*<<< orphan*/  init_task_tag; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; int /*<<< orphan*/  rx_data_octets; } ;
struct TYPE_3__ {scalar_t__ InitialR2T; } ;

/* Variables and functions */
 int CMD_T_ABORTED ; 
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int ICF_GOT_LAST_DATAOUT ; 
 int ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  ISCSI_REASON_BOOKMARK_INVALID ; 
 int SCF_SUPPORTED_SAM_OPCODE ; 
 int /*<<< orphan*/  TCM_UNEXPECTED_UNSOLICITED_DATA ; 
 scalar_t__ TRANSPORT_WRITE_PENDING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_long_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int iscsit_check_pre_dataout (struct iscsi_cmd*,void*) ; 
 int iscsit_dump_data_payload (struct iscsi_conn*,scalar_t__,int) ; 
 int /*<<< orphan*/  iscsit_mod_dataout_timer (struct iscsi_cmd*) ; 
 int iscsit_reject_cmd (struct iscsi_cmd*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  iscsit_stop_dataout_timer (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  transport_send_check_condition_and_sense (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
__iscsit_check_dataout_hdr(struct iscsi_conn *conn, void *buf,
			   struct iscsi_cmd *cmd, u32 payload_length,
			   bool *success)
{
	struct iscsi_data *hdr = buf;
	struct se_cmd *se_cmd;
	int rc;

	/* iSCSI write */
	atomic_long_add(payload_length, &conn->sess->rx_data_octets);

	pr_debug("Got DataOut ITT: 0x%08x, TTT: 0x%08x,"
		" DataSN: 0x%08x, Offset: %u, Length: %u, CID: %hu\n",
		hdr->itt, hdr->ttt, hdr->datasn, ntohl(hdr->offset),
		payload_length, conn->cid);

	if (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT) {
		pr_err("Command ITT: 0x%08x received DataOUT after"
			" last DataOUT received, dumping payload\n",
			cmd->init_task_tag);
		return iscsit_dump_data_payload(conn, payload_length, 1);
	}

	if (cmd->data_direction != DMA_TO_DEVICE) {
		pr_err("Command ITT: 0x%08x received DataOUT for a"
			" NON-WRITE command.\n", cmd->init_task_tag);
		return iscsit_dump_data_payload(conn, payload_length, 1);
	}
	se_cmd = &cmd->se_cmd;
	iscsit_mod_dataout_timer(cmd);

	if ((be32_to_cpu(hdr->offset) + payload_length) > cmd->se_cmd.data_length) {
		pr_err("DataOut Offset: %u, Length %u greater than iSCSI Command EDTL %u, protocol error.\n",
		       be32_to_cpu(hdr->offset), payload_length,
		       cmd->se_cmd.data_length);
		return iscsit_reject_cmd(cmd, ISCSI_REASON_BOOKMARK_INVALID, buf);
	}

	if (cmd->unsolicited_data) {
		int dump_unsolicited_data = 0;

		if (conn->sess->sess_ops->InitialR2T) {
			pr_err("Received unexpected unsolicited data"
				" while InitialR2T=Yes, protocol error.\n");
			transport_send_check_condition_and_sense(&cmd->se_cmd,
					TCM_UNEXPECTED_UNSOLICITED_DATA, 0);
			return -1;
		}
		/*
		 * Special case for dealing with Unsolicited DataOUT
		 * and Unsupported SAM WRITE Opcodes and SE resource allocation
		 * failures;
		 */

		/* Something's amiss if we're not in WRITE_PENDING state... */
		WARN_ON(se_cmd->t_state != TRANSPORT_WRITE_PENDING);
		if (!(se_cmd->se_cmd_flags & SCF_SUPPORTED_SAM_OPCODE))
			dump_unsolicited_data = 1;

		if (dump_unsolicited_data) {
			/*
			 * Check if a delayed TASK_ABORTED status needs to
			 * be sent now if the ISCSI_FLAG_CMD_FINAL has been
			 * received with the unsolicited data out.
			 */
			if (hdr->flags & ISCSI_FLAG_CMD_FINAL)
				iscsit_stop_dataout_timer(cmd);

			return iscsit_dump_data_payload(conn, payload_length, 1);
		}
	} else {
		/*
		 * For the normal solicited data path:
		 *
		 * Check for a delayed TASK_ABORTED status and dump any
		 * incoming data out payload if one exists.  Also, when the
		 * ISCSI_FLAG_CMD_FINAL is set to denote the end of the current
		 * data out sequence, we decrement outstanding_r2ts.  Once
		 * outstanding_r2ts reaches zero, go ahead and send the delayed
		 * TASK_ABORTED status.
		 */
		if (se_cmd->transport_state & CMD_T_ABORTED) {
			if (hdr->flags & ISCSI_FLAG_CMD_FINAL &&
			    --cmd->outstanding_r2ts < 1)
				iscsit_stop_dataout_timer(cmd);

			return iscsit_dump_data_payload(conn, payload_length, 1);
		}
	}
	/*
	 * Perform DataSN, DataSequenceInOrder, DataPDUInOrder, and
	 * within-command recovery checks before receiving the payload.
	 */
	rc = iscsit_check_pre_dataout(cmd, buf);
	if (rc == DATAOUT_WITHIN_COMMAND_RECOVERY)
		return 0;
	else if (rc == DATAOUT_CANNOT_RECOVER)
		return -1;
	*success = true;
	return 0;
}