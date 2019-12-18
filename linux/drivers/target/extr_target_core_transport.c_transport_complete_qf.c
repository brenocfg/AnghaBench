#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct se_cmd {scalar_t__ t_state; int se_cmd_flags; int data_direction; int /*<<< orphan*/  se_dev; TYPE_1__* se_tfo; scalar_t__ scsi_status; } ;
struct TYPE_2__ {int (* queue_data_in ) (struct se_cmd*) ;int (* queue_status ) (struct se_cmd*) ;} ;

/* Variables and functions */
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int SCF_BIDI ; 
 int SCF_TRANSPORT_TASK_SENSE ; 
 int SCF_TREAT_READ_AS_NORMAL ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 scalar_t__ TRANSPORT_COMPLETE_QF_ERR ; 
 int stub1 (struct se_cmd*) ; 
 int stub2 (struct se_cmd*) ; 
 int stub3 (struct se_cmd*) ; 
 int /*<<< orphan*/  trace_target_cmd_complete (struct se_cmd*) ; 
 int /*<<< orphan*/  translate_sense_reason (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_cmd_check_stop_to_fabric (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_complete_task_attr (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_handle_queue_full (struct se_cmd*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void transport_complete_qf(struct se_cmd *cmd)
{
	int ret = 0;

	transport_complete_task_attr(cmd);
	/*
	 * If a fabric driver ->write_pending() or ->queue_data_in() callback
	 * has returned neither -ENOMEM or -EAGAIN, assume it's fatal and
	 * the same callbacks should not be retried.  Return CHECK_CONDITION
	 * if a scsi_status is not already set.
	 *
	 * If a fabric driver ->queue_status() has returned non zero, always
	 * keep retrying no matter what..
	 */
	if (cmd->t_state == TRANSPORT_COMPLETE_QF_ERR) {
		if (cmd->scsi_status)
			goto queue_status;

		translate_sense_reason(cmd, TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE);
		goto queue_status;
	}

	/*
	 * Check if we need to send a sense buffer from
	 * the struct se_cmd in question. We do NOT want
	 * to take this path of the IO has been marked as
	 * needing to be treated like a "normal read". This
	 * is the case if it's a tape read, and either the
	 * FM, EOM, or ILI bits are set, but there is no
	 * sense data.
	 */
	if (!(cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL) &&
	    cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE)
		goto queue_status;

	switch (cmd->data_direction) {
	case DMA_FROM_DEVICE:
		/* queue status if not treating this as a normal read */
		if (cmd->scsi_status &&
		    !(cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL))
			goto queue_status;

		trace_target_cmd_complete(cmd);
		ret = cmd->se_tfo->queue_data_in(cmd);
		break;
	case DMA_TO_DEVICE:
		if (cmd->se_cmd_flags & SCF_BIDI) {
			ret = cmd->se_tfo->queue_data_in(cmd);
			break;
		}
		/* fall through */
	case DMA_NONE:
queue_status:
		trace_target_cmd_complete(cmd);
		ret = cmd->se_tfo->queue_status(cmd);
		break;
	default:
		break;
	}

	if (ret < 0) {
		transport_handle_queue_full(cmd, cmd->se_dev, ret, false);
		return;
	}
	transport_cmd_check_stop_to_fabric(cmd);
}