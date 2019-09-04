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
struct ena_comp_ctx {scalar_t__ status; int /*<<< orphan*/  comp_status; int /*<<< orphan*/  cmd_opcode; int /*<<< orphan*/  wait_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_completion; } ;
struct ena_com_admin_queue {int running_state; int /*<<< orphan*/  q_lock; TYPE_1__ stats; int /*<<< orphan*/  completion_timeout; } ;

/* Variables and functions */
 scalar_t__ ENA_CMD_COMPLETED ; 
 scalar_t__ ENA_CMD_SUBMITTED ; 
 int ETIME ; 
 int /*<<< orphan*/  comp_ctxt_release (struct ena_com_admin_queue*,struct ena_comp_ctx*) ; 
 int ena_com_comp_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_handle_admin_completion (struct ena_com_admin_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ena_com_wait_and_process_admin_cq_interrupts(struct ena_comp_ctx *comp_ctx,
							struct ena_com_admin_queue *admin_queue)
{
	unsigned long flags;
	int ret;

	wait_for_completion_timeout(&comp_ctx->wait_event,
				    usecs_to_jiffies(
					    admin_queue->completion_timeout));

	/* In case the command wasn't completed find out the root cause.
	 * There might be 2 kinds of errors
	 * 1) No completion (timeout reached)
	 * 2) There is completion but the device didn't get any msi-x interrupt.
	 */
	if (unlikely(comp_ctx->status == ENA_CMD_SUBMITTED)) {
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		ena_com_handle_admin_completion(admin_queue);
		admin_queue->stats.no_completion++;
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);

		if (comp_ctx->status == ENA_CMD_COMPLETED)
			pr_err("The ena device have completion but the driver didn't receive any MSI-X interrupt (cmd %d)\n",
			       comp_ctx->cmd_opcode);
		else
			pr_err("The ena device doesn't send any completion for the admin cmd %d status %d\n",
			       comp_ctx->cmd_opcode, comp_ctx->status);

		admin_queue->running_state = false;
		ret = -ETIME;
		goto err;
	}

	ret = ena_com_comp_status_to_errno(comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	return ret;
}