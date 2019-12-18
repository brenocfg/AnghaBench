#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct request_queue {struct mmc_queue* queuedata; } ;
struct request {struct request_queue* q; } ;
struct mmc_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  use_cqe; scalar_t__ recovery_needed; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;

/* Variables and functions */
 int BLK_EH_RESET_TIMER ; 
 int mmc_cqe_timed_out (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static enum blk_eh_timer_return mmc_mq_timed_out(struct request *req,
						 bool reserved)
{
	struct request_queue *q = req->q;
	struct mmc_queue *mq = q->queuedata;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&mq->lock, flags);

	if (mq->recovery_needed || !mq->use_cqe)
		ret = BLK_EH_RESET_TIMER;
	else
		ret = mmc_cqe_timed_out(req);

	spin_unlock_irqrestore(&mq->lock, flags);

	return ret;
}