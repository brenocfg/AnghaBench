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
struct efa_comp_ctx {scalar_t__ status; int /*<<< orphan*/  comp_status; } ;
struct TYPE_4__ {int /*<<< orphan*/  no_completion; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct efa_com_admin_queue {int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  state; TYPE_2__ stats; int /*<<< orphan*/  efa_dev; TYPE_1__ cq; int /*<<< orphan*/  completion_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_AQ_STATE_RUNNING_BIT ; 
 scalar_t__ EFA_CMD_SUBMITTED ; 
 int ETIME ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int efa_com_comp_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efa_com_handle_admin_completion (struct efa_com_admin_queue*) ; 
 int /*<<< orphan*/  efa_com_put_comp_ctx (struct efa_com_admin_queue*,struct efa_comp_ctx*) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_com_wait_and_process_admin_cq_polling(struct efa_comp_ctx *comp_ctx,
						     struct efa_com_admin_queue *aq)
{
	unsigned long timeout;
	unsigned long flags;
	int err;

	timeout = jiffies + usecs_to_jiffies(aq->completion_timeout);

	while (1) {
		spin_lock_irqsave(&aq->cq.lock, flags);
		efa_com_handle_admin_completion(aq);
		spin_unlock_irqrestore(&aq->cq.lock, flags);

		if (comp_ctx->status != EFA_CMD_SUBMITTED)
			break;

		if (time_is_before_jiffies(timeout)) {
			ibdev_err_ratelimited(
				aq->efa_dev,
				"Wait for completion (polling) timeout\n");
			/* EFA didn't have any completion */
			atomic64_inc(&aq->stats.no_completion);

			clear_bit(EFA_AQ_STATE_RUNNING_BIT, &aq->state);
			err = -ETIME;
			goto out;
		}

		msleep(aq->poll_interval);
	}

	err = efa_com_comp_status_to_errno(comp_ctx->comp_status);
out:
	efa_com_put_comp_ctx(aq, comp_ctx);
	return err;
}