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
struct ena_comp_ctx {scalar_t__ status; int /*<<< orphan*/  comp_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  aborted_cmd; int /*<<< orphan*/  no_completion; } ;
struct ena_com_admin_queue {int running_state; int /*<<< orphan*/  q_lock; TYPE_1__ stats; int /*<<< orphan*/  completion_timeout; } ;

/* Variables and functions */
 scalar_t__ ENA_CMD_ABORTED ; 
 scalar_t__ ENA_CMD_COMPLETED ; 
 scalar_t__ ENA_CMD_SUBMITTED ; 
 int /*<<< orphan*/  ENA_POLL_MS ; 
 int ENODEV ; 
 int ETIME ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  comp_ctxt_release (struct ena_com_admin_queue*,struct ena_comp_ctx*) ; 
 int ena_com_comp_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_handle_admin_completion (struct ena_com_admin_queue*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ena_com_wait_and_process_admin_cq_polling(struct ena_comp_ctx *comp_ctx,
						     struct ena_com_admin_queue *admin_queue)
{
	unsigned long flags = 0;
	unsigned long timeout;
	int ret;

	timeout = jiffies + usecs_to_jiffies(admin_queue->completion_timeout);

	while (1) {
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		ena_com_handle_admin_completion(admin_queue);
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);

		if (comp_ctx->status != ENA_CMD_SUBMITTED)
			break;

		if (time_is_before_jiffies(timeout)) {
			pr_err("Wait for completion (polling) timeout\n");
			/* ENA didn't have any completion */
			spin_lock_irqsave(&admin_queue->q_lock, flags);
			admin_queue->stats.no_completion++;
			admin_queue->running_state = false;
			spin_unlock_irqrestore(&admin_queue->q_lock, flags);

			ret = -ETIME;
			goto err;
		}

		msleep(ENA_POLL_MS);
	}

	if (unlikely(comp_ctx->status == ENA_CMD_ABORTED)) {
		pr_err("Command was aborted\n");
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		admin_queue->stats.aborted_cmd++;
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);
		ret = -ENODEV;
		goto err;
	}

	WARN(comp_ctx->status != ENA_CMD_COMPLETED, "Invalid comp status %d\n",
	     comp_ctx->status);

	ret = ena_com_comp_status_to_errno(comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	return ret;
}