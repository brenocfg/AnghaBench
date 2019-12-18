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
struct iscsi_seq {scalar_t__ type; int pdu_count; int pdu_start; int /*<<< orphan*/  status; scalar_t__ next_burst_len; scalar_t__ orig_offset; scalar_t__ offset; scalar_t__ data_sn; } ;
struct iscsi_pdu {scalar_t__ status; scalar_t__ offset; scalar_t__ length; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {scalar_t__ first_burst_len; scalar_t__ seq_start_offset; int pdu_count; scalar_t__ seq_end_offset; int seq_count; struct iscsi_pdu* pdu_list; int /*<<< orphan*/  write_data_done; struct iscsi_seq* seq_list; scalar_t__ immediate_data; int /*<<< orphan*/  r2t_offset; scalar_t__ data_sn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {scalar_t__ DataPDUInOrder; scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY ; 
 void* ISCSI_PDU_NOT_RECEIVED ; 
 scalar_t__ ISCSI_PDU_RECEIVED_OK ; 
 scalar_t__ SEQTYPE_UNSOLICITED ; 

__attribute__((used)) static void iscsit_task_reassign_prepare_unsolicited_dataout(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn)
{
	int i, j;
	struct iscsi_pdu *pdu = NULL;
	struct iscsi_seq *seq = NULL;

	if (conn->sess->sess_ops->DataSequenceInOrder) {
		cmd->data_sn = 0;

		if (cmd->immediate_data)
			cmd->r2t_offset += (cmd->first_burst_len -
				cmd->seq_start_offset);

		if (conn->sess->sess_ops->DataPDUInOrder) {
			cmd->write_data_done -= (cmd->immediate_data) ?
						(cmd->first_burst_len -
						 cmd->seq_start_offset) :
						 cmd->first_burst_len;
			cmd->first_burst_len = 0;
			return;
		}

		for (i = 0; i < cmd->pdu_count; i++) {
			pdu = &cmd->pdu_list[i];

			if (pdu->status != ISCSI_PDU_RECEIVED_OK)
				continue;

			if ((pdu->offset >= cmd->seq_start_offset) &&
			   ((pdu->offset + pdu->length) <=
			     cmd->seq_end_offset)) {
				cmd->first_burst_len -= pdu->length;
				cmd->write_data_done -= pdu->length;
				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			}
		}
	} else {
		for (i = 0; i < cmd->seq_count; i++) {
			seq = &cmd->seq_list[i];

			if (seq->type != SEQTYPE_UNSOLICITED)
				continue;

			cmd->write_data_done -=
					(seq->offset - seq->orig_offset);
			cmd->first_burst_len = 0;
			seq->data_sn = 0;
			seq->offset = seq->orig_offset;
			seq->next_burst_len = 0;
			seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY;

			if (conn->sess->sess_ops->DataPDUInOrder)
				continue;

			for (j = 0; j < seq->pdu_count; j++) {
				pdu = &cmd->pdu_list[j+seq->pdu_start];

				if (pdu->status != ISCSI_PDU_RECEIVED_OK)
					continue;

				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			}
		}
	}
}