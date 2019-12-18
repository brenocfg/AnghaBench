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
struct iscsi_seq {scalar_t__ next_burst_len; scalar_t__ xfer_len; void* status; int /*<<< orphan*/  offset; int /*<<< orphan*/  data_sn; } ;
struct iscsi_data {int flags; int /*<<< orphan*/  datasn; int /*<<< orphan*/  offset; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct TYPE_6__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ first_burst_len; scalar_t__ next_burst_len; scalar_t__ write_data_done; TYPE_3__ se_cmd; scalar_t__ data_sn; struct iscsi_seq* seq_ptr; scalar_t__ unsolicited_data; struct iscsi_conn* conn; } ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {scalar_t__ FirstBurstLength; scalar_t__ MaxBurstLength; scalar_t__ DataSequenceInOrder; int /*<<< orphan*/  DataPDUInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
 int DATAOUT_SEND_R2T ; 
 int DATAOUT_SEND_TO_TRANSPORT ; 
 void* DATAOUT_SEQUENCE_COMPLETE ; 
 int ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int iscsit_dataout_update_datapduinorder_no (struct iscsi_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ iscsit_dataout_update_r2t (struct iscsi_cmd*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_dataout_post_crc_passed(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	int ret, send_r2t = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_seq *seq = NULL;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	if (cmd->unsolicited_data) {
		if ((cmd->first_burst_len + payload_length) ==
		     conn->sess->sess_ops->FirstBurstLength) {
			if (iscsit_dataout_update_r2t(cmd, be32_to_cpu(hdr->offset),
					payload_length) < 0)
				return DATAOUT_CANNOT_RECOVER;
			send_r2t = 1;
		}

		if (!conn->sess->sess_ops->DataPDUInOrder) {
			ret = iscsit_dataout_update_datapduinorder_no(cmd,
				be32_to_cpu(hdr->datasn),
				(hdr->flags & ISCSI_FLAG_CMD_FINAL));
			if (ret == DATAOUT_CANNOT_RECOVER)
				return ret;
		}

		cmd->first_burst_len += payload_length;

		if (conn->sess->sess_ops->DataSequenceInOrder)
			cmd->data_sn++;
		else {
			seq = cmd->seq_ptr;
			seq->data_sn++;
			seq->offset += payload_length;
		}

		if (send_r2t) {
			if (seq)
				seq->status = DATAOUT_SEQUENCE_COMPLETE;
			cmd->first_burst_len = 0;
			cmd->unsolicited_data = 0;
		}
	} else {
		if (conn->sess->sess_ops->DataSequenceInOrder) {
			if ((cmd->next_burst_len + payload_length) ==
			     conn->sess->sess_ops->MaxBurstLength) {
				if (iscsit_dataout_update_r2t(cmd,
						be32_to_cpu(hdr->offset),
						payload_length) < 0)
					return DATAOUT_CANNOT_RECOVER;
				send_r2t = 1;
			}

			if (!conn->sess->sess_ops->DataPDUInOrder) {
				ret = iscsit_dataout_update_datapduinorder_no(
						cmd, be32_to_cpu(hdr->datasn),
						(hdr->flags & ISCSI_FLAG_CMD_FINAL));
				if (ret == DATAOUT_CANNOT_RECOVER)
					return ret;
			}

			cmd->next_burst_len += payload_length;
			cmd->data_sn++;

			if (send_r2t)
				cmd->next_burst_len = 0;
		} else {
			seq = cmd->seq_ptr;

			if ((seq->next_burst_len + payload_length) ==
			     seq->xfer_len) {
				if (iscsit_dataout_update_r2t(cmd,
						be32_to_cpu(hdr->offset),
						payload_length) < 0)
					return DATAOUT_CANNOT_RECOVER;
				send_r2t = 1;
			}

			if (!conn->sess->sess_ops->DataPDUInOrder) {
				ret = iscsit_dataout_update_datapduinorder_no(
						cmd, be32_to_cpu(hdr->datasn),
						(hdr->flags & ISCSI_FLAG_CMD_FINAL));
				if (ret == DATAOUT_CANNOT_RECOVER)
					return ret;
			}

			seq->data_sn++;
			seq->offset += payload_length;
			seq->next_burst_len += payload_length;

			if (send_r2t) {
				seq->next_burst_len = 0;
				seq->status = DATAOUT_SEQUENCE_COMPLETE;
			}
		}
	}

	if (send_r2t && conn->sess->sess_ops->DataSequenceInOrder)
		cmd->data_sn = 0;

	cmd->write_data_done += payload_length;

	if (cmd->write_data_done == cmd->se_cmd.data_length)
		return DATAOUT_SEND_TO_TRANSPORT;
	else if (send_r2t)
		return DATAOUT_SEND_R2T;
	else
		return DATAOUT_NORMAL;
}