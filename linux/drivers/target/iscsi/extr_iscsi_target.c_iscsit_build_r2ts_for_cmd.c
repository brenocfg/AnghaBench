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
typedef  int u32 ;
struct iscsi_seq {int offset; int xfer_len; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct TYPE_6__ {int data_length; } ;
struct iscsi_cmd {int cmd_flags; int r2t_offset; scalar_t__ outstanding_r2ts; int next_burst_len; scalar_t__ seq_send_order; scalar_t__ seq_count; int /*<<< orphan*/  r2t_lock; TYPE_3__ se_cmd; int /*<<< orphan*/  write_data_done; } ;
typedef  scalar_t__ s32 ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {scalar_t__ MaxOutstandingR2T; int MaxBurstLength; scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 int ICF_SENT_LAST_R2T ; 
 scalar_t__ iscsit_add_r2t_to_list (struct iscsi_cmd*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_seq* iscsit_get_seq_holder_for_r2t (struct iscsi_cmd*) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iscsit_build_r2ts_for_cmd(
	struct iscsi_conn *conn,
	struct iscsi_cmd *cmd,
	bool recovery)
{
	int first_r2t = 1;
	u32 offset = 0, xfer_len = 0;

	spin_lock_bh(&cmd->r2t_lock);
	if (cmd->cmd_flags & ICF_SENT_LAST_R2T) {
		spin_unlock_bh(&cmd->r2t_lock);
		return 0;
	}

	if (conn->sess->sess_ops->DataSequenceInOrder &&
	    !recovery)
		cmd->r2t_offset = max(cmd->r2t_offset, cmd->write_data_done);

	while (cmd->outstanding_r2ts < conn->sess->sess_ops->MaxOutstandingR2T) {
		if (conn->sess->sess_ops->DataSequenceInOrder) {
			offset = cmd->r2t_offset;

			if (first_r2t && recovery) {
				int new_data_end = offset +
					conn->sess->sess_ops->MaxBurstLength -
					cmd->next_burst_len;

				if (new_data_end > cmd->se_cmd.data_length)
					xfer_len = cmd->se_cmd.data_length - offset;
				else
					xfer_len =
						conn->sess->sess_ops->MaxBurstLength -
						cmd->next_burst_len;
			} else {
				int new_data_end = offset +
					conn->sess->sess_ops->MaxBurstLength;

				if (new_data_end > cmd->se_cmd.data_length)
					xfer_len = cmd->se_cmd.data_length - offset;
				else
					xfer_len = conn->sess->sess_ops->MaxBurstLength;
			}

			if ((s32)xfer_len < 0) {
				cmd->cmd_flags |= ICF_SENT_LAST_R2T;
				break;
			}

			cmd->r2t_offset += xfer_len;

			if (cmd->r2t_offset == cmd->se_cmd.data_length)
				cmd->cmd_flags |= ICF_SENT_LAST_R2T;
		} else {
			struct iscsi_seq *seq;

			seq = iscsit_get_seq_holder_for_r2t(cmd);
			if (!seq) {
				spin_unlock_bh(&cmd->r2t_lock);
				return -1;
			}

			offset = seq->offset;
			xfer_len = seq->xfer_len;

			if (cmd->seq_send_order == cmd->seq_count)
				cmd->cmd_flags |= ICF_SENT_LAST_R2T;
		}
		cmd->outstanding_r2ts++;
		first_r2t = 0;

		if (iscsit_add_r2t_to_list(cmd, offset, xfer_len, 0, 0) < 0) {
			spin_unlock_bh(&cmd->r2t_lock);
			return -1;
		}

		if (cmd->cmd_flags & ICF_SENT_LAST_R2T)
			break;
	}
	spin_unlock_bh(&cmd->r2t_lock);

	return 0;
}