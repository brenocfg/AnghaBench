#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iscsi_data {int flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct TYPE_6__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ seq_start_offset; scalar_t__ seq_end_offset; scalar_t__ init_task_tag; scalar_t__ first_burst_len; TYPE_3__ se_cmd; struct iscsi_conn* conn; } ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {scalar_t__ FirstBurstLength; int /*<<< orphan*/  DataPDUInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
 int ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  TCM_INCORRECT_AMOUNT_OF_DATA ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  transport_send_check_condition_and_sense (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_dataout_check_unsolicited_sequence(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	u32 first_burst_len;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);


	if ((be32_to_cpu(hdr->offset) < cmd->seq_start_offset) ||
	   ((be32_to_cpu(hdr->offset) + payload_length) > cmd->seq_end_offset)) {
		pr_err("Command ITT: 0x%08x with Offset: %u,"
		" Length: %u outside of Unsolicited Sequence %u:%u while"
		" DataSequenceInOrder=Yes.\n", cmd->init_task_tag,
		be32_to_cpu(hdr->offset), payload_length, cmd->seq_start_offset,
			cmd->seq_end_offset);
		return DATAOUT_CANNOT_RECOVER;
	}

	first_burst_len = (cmd->first_burst_len + payload_length);

	if (first_burst_len > conn->sess->sess_ops->FirstBurstLength) {
		pr_err("Total %u bytes exceeds FirstBurstLength: %u"
			" for this Unsolicited DataOut Burst.\n",
			first_burst_len, conn->sess->sess_ops->FirstBurstLength);
		transport_send_check_condition_and_sense(&cmd->se_cmd,
				TCM_INCORRECT_AMOUNT_OF_DATA, 0);
		return DATAOUT_CANNOT_RECOVER;
	}

	/*
	 * Perform various MaxBurstLength and ISCSI_FLAG_CMD_FINAL sanity
	 * checks for the current Unsolicited DataOUT Sequence.
	 */
	if (hdr->flags & ISCSI_FLAG_CMD_FINAL) {
		/*
		 * Ignore ISCSI_FLAG_CMD_FINAL checks while DataPDUInOrder=No, end of
		 * sequence checks are handled in
		 * iscsit_dataout_datapduinorder_no_fbit().
		 */
		if (!conn->sess->sess_ops->DataPDUInOrder)
			goto out;

		if ((first_burst_len != cmd->se_cmd.data_length) &&
		    (first_burst_len != conn->sess->sess_ops->FirstBurstLength)) {
			pr_err("Unsolicited non-immediate data"
			" received %u does not equal FirstBurstLength: %u, and"
			" does not equal ExpXferLen %u.\n", first_burst_len,
				conn->sess->sess_ops->FirstBurstLength,
				cmd->se_cmd.data_length);
			transport_send_check_condition_and_sense(&cmd->se_cmd,
					TCM_INCORRECT_AMOUNT_OF_DATA, 0);
			return DATAOUT_CANNOT_RECOVER;
		}
	} else {
		if (first_burst_len == conn->sess->sess_ops->FirstBurstLength) {
			pr_err("Command ITT: 0x%08x reached"
			" FirstBurstLength: %u, but ISCSI_FLAG_CMD_FINAL is not set. protocol"
				" error.\n", cmd->init_task_tag,
				conn->sess->sess_ops->FirstBurstLength);
			return DATAOUT_CANNOT_RECOVER;
		}
		if (first_burst_len == cmd->se_cmd.data_length) {
			pr_err("Command ITT: 0x%08x reached"
			" ExpXferLen: %u, but ISCSI_FLAG_CMD_FINAL is not set. protocol"
			" error.\n", cmd->init_task_tag, cmd->se_cmd.data_length);
			return DATAOUT_CANNOT_RECOVER;
		}
	}

out:
	return DATAOUT_NORMAL;
}