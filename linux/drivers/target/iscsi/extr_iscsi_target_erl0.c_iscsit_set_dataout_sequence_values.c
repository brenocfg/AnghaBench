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
struct iscsi_conn {TYPE_3__* sess; } ;
struct TYPE_4__ {scalar_t__ data_length; } ;
struct iscsi_cmd {scalar_t__ seq_start_offset; scalar_t__ write_data_done; scalar_t__ seq_end_offset; TYPE_1__ se_cmd; scalar_t__ unsolicited_data; struct iscsi_conn* conn; } ;
struct TYPE_6__ {TYPE_2__* sess_ops; } ;
struct TYPE_5__ {scalar_t__ MaxBurstLength; int /*<<< orphan*/  DataSequenceInOrder; int /*<<< orphan*/  FirstBurstLength; } ;

/* Variables and functions */
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 

void iscsit_set_dataout_sequence_values(
	struct iscsi_cmd *cmd)
{
	struct iscsi_conn *conn = cmd->conn;
	/*
	 * Still set seq_start_offset and seq_end_offset for Unsolicited
	 * DataOUT, even if DataSequenceInOrder=No.
	 */
	if (cmd->unsolicited_data) {
		cmd->seq_start_offset = cmd->write_data_done;
		cmd->seq_end_offset = min(cmd->se_cmd.data_length,
					conn->sess->sess_ops->FirstBurstLength);
		return;
	}

	if (!conn->sess->sess_ops->DataSequenceInOrder)
		return;

	if (!cmd->seq_start_offset && !cmd->seq_end_offset) {
		cmd->seq_start_offset = cmd->write_data_done;
		cmd->seq_end_offset = (cmd->se_cmd.data_length >
			conn->sess->sess_ops->MaxBurstLength) ?
			(cmd->write_data_done +
			conn->sess->sess_ops->MaxBurstLength) : cmd->se_cmd.data_length;
	} else {
		cmd->seq_start_offset = cmd->seq_end_offset;
		cmd->seq_end_offset = ((cmd->seq_end_offset +
			conn->sess->sess_ops->MaxBurstLength) >=
			cmd->se_cmd.data_length) ? cmd->se_cmd.data_length :
			(cmd->seq_end_offset +
			 conn->sess->sess_ops->MaxBurstLength);
	}
}