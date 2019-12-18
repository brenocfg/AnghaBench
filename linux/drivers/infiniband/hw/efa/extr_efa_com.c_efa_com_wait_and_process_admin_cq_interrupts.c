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
struct efa_comp_ctx {scalar_t__ status; int /*<<< orphan*/  comp_status; int /*<<< orphan*/  cmd_opcode; int /*<<< orphan*/  wait_event; } ;
struct TYPE_6__ {int /*<<< orphan*/  cc; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  cc; int /*<<< orphan*/  pc; } ;
struct TYPE_4__ {int /*<<< orphan*/  no_completion; } ;
struct efa_com_admin_queue {int /*<<< orphan*/  state; TYPE_3__ cq; TYPE_2__ sq; int /*<<< orphan*/  efa_dev; TYPE_1__ stats; int /*<<< orphan*/  completion_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_AQ_STATE_RUNNING_BIT ; 
 scalar_t__ EFA_CMD_COMPLETED ; 
 scalar_t__ EFA_CMD_SUBMITTED ; 
 int ETIME ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efa_com_cmd_str (int /*<<< orphan*/ ) ; 
 int efa_com_comp_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efa_com_handle_admin_completion (struct efa_com_admin_queue*) ; 
 int /*<<< orphan*/  efa_com_put_comp_ctx (struct efa_com_admin_queue*,struct efa_comp_ctx*) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct efa_comp_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_com_wait_and_process_admin_cq_interrupts(struct efa_comp_ctx *comp_ctx,
							struct efa_com_admin_queue *aq)
{
	unsigned long flags;
	int err;

	wait_for_completion_timeout(&comp_ctx->wait_event,
				    usecs_to_jiffies(aq->completion_timeout));

	/*
	 * In case the command wasn't completed find out the root cause.
	 * There might be 2 kinds of errors
	 * 1) No completion (timeout reached)
	 * 2) There is completion but the device didn't get any msi-x interrupt.
	 */
	if (comp_ctx->status == EFA_CMD_SUBMITTED) {
		spin_lock_irqsave(&aq->cq.lock, flags);
		efa_com_handle_admin_completion(aq);
		spin_unlock_irqrestore(&aq->cq.lock, flags);

		atomic64_inc(&aq->stats.no_completion);

		if (comp_ctx->status == EFA_CMD_COMPLETED)
			ibdev_err_ratelimited(
				aq->efa_dev,
				"The device sent a completion but the driver didn't receive any MSI-X interrupt for admin cmd %s(%d) status %d (ctx: 0x%p, sq producer: %d, sq consumer: %d, cq consumer: %d)\n",
				efa_com_cmd_str(comp_ctx->cmd_opcode),
				comp_ctx->cmd_opcode, comp_ctx->status,
				comp_ctx, aq->sq.pc, aq->sq.cc, aq->cq.cc);
		else
			ibdev_err_ratelimited(
				aq->efa_dev,
				"The device didn't send any completion for admin cmd %s(%d) status %d (ctx 0x%p, sq producer: %d, sq consumer: %d, cq consumer: %d)\n",
				efa_com_cmd_str(comp_ctx->cmd_opcode),
				comp_ctx->cmd_opcode, comp_ctx->status,
				comp_ctx, aq->sq.pc, aq->sq.cc, aq->cq.cc);

		clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);
		err = -ETIME;
		goto out;
	}

	err = efa_com_comp_status_to_errno(comp_ctx->comp_status);
out:
	efa_com_put_comp_ctx(aq, comp_ctx);
	return err;
}