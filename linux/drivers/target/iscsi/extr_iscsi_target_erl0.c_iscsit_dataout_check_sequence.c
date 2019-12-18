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
struct iscsi_seq {scalar_t__ status; scalar_t__ next_burst_len; scalar_t__ xfer_len; } ;
struct iscsi_data {int flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct TYPE_6__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ seq_start_offset; scalar_t__ seq_end_offset; scalar_t__ next_burst_len; scalar_t__ write_data_done; int /*<<< orphan*/  init_task_tag; TYPE_3__ se_cmd; struct iscsi_seq* seq_ptr; struct iscsi_conn* conn; } ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {scalar_t__ MaxBurstLength; scalar_t__ DataSequenceInOrder; int /*<<< orphan*/  DataPDUInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
 scalar_t__ DATAOUT_SEQUENCE_COMPLETE ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 int ISCSI_FLAG_CMD_FINAL ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ iscsit_dump_data_payload (struct iscsi_conn*,scalar_t__,int) ; 
 struct iscsi_seq* iscsit_get_seq_holder (struct iscsi_cmd*,scalar_t__,scalar_t__) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int iscsit_dataout_check_sequence(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	u32 next_burst_len;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_seq *seq = NULL;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * For DataSequenceInOrder=Yes: Check that the offset and offset+length
	 * is within range as defined by iscsi_set_dataout_sequence_values().
	 *
	 * For DataSequenceInOrder=No: Check that an struct iscsi_seq exists for
	 * offset+length tuple.
	 */
	if (conn->sess->sess_ops->DataSequenceInOrder) {
		/*
		 * Due to possibility of recovery DataOUT sent by the initiator
		 * fullfilling an Recovery R2T, it's best to just dump the
		 * payload here, instead of erroring out.
		 */
		if ((be32_to_cpu(hdr->offset) < cmd->seq_start_offset) ||
		   ((be32_to_cpu(hdr->offset) + payload_length) > cmd->seq_end_offset)) {
			pr_err("Command ITT: 0x%08x with Offset: %u,"
			" Length: %u outside of Sequence %u:%u while"
			" DataSequenceInOrder=Yes.\n", cmd->init_task_tag,
			be32_to_cpu(hdr->offset), payload_length, cmd->seq_start_offset,
				cmd->seq_end_offset);

			if (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
				return DATAOUT_CANNOT_RECOVER;
			return DATAOUT_WITHIN_COMMAND_RECOVERY;
		}

		next_burst_len = (cmd->next_burst_len + payload_length);
	} else {
		seq = iscsit_get_seq_holder(cmd, be32_to_cpu(hdr->offset),
					    payload_length);
		if (!seq)
			return DATAOUT_CANNOT_RECOVER;
		/*
		 * Set the struct iscsi_seq pointer to reuse later.
		 */
		cmd->seq_ptr = seq;

		if (seq->status == DATAOUT_SEQUENCE_COMPLETE) {
			if (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
				return DATAOUT_CANNOT_RECOVER;
			return DATAOUT_WITHIN_COMMAND_RECOVERY;
		}

		next_burst_len = (seq->next_burst_len + payload_length);
	}

	if (next_burst_len > conn->sess->sess_ops->MaxBurstLength) {
		pr_err("Command ITT: 0x%08x, NextBurstLength: %u and"
			" Length: %u exceeds MaxBurstLength: %u. protocol"
			" error.\n", cmd->init_task_tag,
			(next_burst_len - payload_length),
			payload_length, conn->sess->sess_ops->MaxBurstLength);
		return DATAOUT_CANNOT_RECOVER;
	}

	/*
	 * Perform various MaxBurstLength and ISCSI_FLAG_CMD_FINAL sanity
	 * checks for the current DataOUT Sequence.
	 */
	if (hdr->flags & ISCSI_FLAG_CMD_FINAL) {
		/*
		 * Ignore ISCSI_FLAG_CMD_FINAL checks while DataPDUInOrder=No, end of
		 * sequence checks are handled in
		 * iscsit_dataout_datapduinorder_no_fbit().
		 */
		if (!conn->sess->sess_ops->DataPDUInOrder)
			goto out;

		if (conn->sess->sess_ops->DataSequenceInOrder) {
			if ((next_burst_len <
			     conn->sess->sess_ops->MaxBurstLength) &&
			   ((cmd->write_data_done + payload_length) <
			     cmd->se_cmd.data_length)) {
				pr_err("Command ITT: 0x%08x set ISCSI_FLAG_CMD_FINAL"
				" before end of DataOUT sequence, protocol"
				" error.\n", cmd->init_task_tag);
				return DATAOUT_CANNOT_RECOVER;
			}
		} else {
			if (next_burst_len < seq->xfer_len) {
				pr_err("Command ITT: 0x%08x set ISCSI_FLAG_CMD_FINAL"
				" before end of DataOUT sequence, protocol"
				" error.\n", cmd->init_task_tag);
				return DATAOUT_CANNOT_RECOVER;
			}
		}
	} else {
		if (conn->sess->sess_ops->DataSequenceInOrder) {
			if (next_burst_len ==
					conn->sess->sess_ops->MaxBurstLength) {
				pr_err("Command ITT: 0x%08x reached"
				" MaxBurstLength: %u, but ISCSI_FLAG_CMD_FINAL is"
				" not set, protocol error.", cmd->init_task_tag,
					conn->sess->sess_ops->MaxBurstLength);
				return DATAOUT_CANNOT_RECOVER;
			}
			if ((cmd->write_data_done + payload_length) ==
					cmd->se_cmd.data_length) {
				pr_err("Command ITT: 0x%08x reached"
				" last DataOUT PDU in sequence but ISCSI_FLAG_"
				"CMD_FINAL is not set, protocol error.\n",
					cmd->init_task_tag);
				return DATAOUT_CANNOT_RECOVER;
			}
		} else {
			if (next_burst_len == seq->xfer_len) {
				pr_err("Command ITT: 0x%08x reached"
				" last DataOUT PDU in sequence but ISCSI_FLAG_"
				"CMD_FINAL is not set, protocol error.\n",
					cmd->init_task_tag);
				return DATAOUT_CANNOT_RECOVER;
			}
		}
	}

out:
	return DATAOUT_NORMAL;
}