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
struct mmc_queue {int waiting; int /*<<< orphan*/  lock; int /*<<< orphan*/  rw_wait; scalar_t__ recovery_needed; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool mmc_blk_rw_wait_cond(struct mmc_queue *mq, int *err)
{
	unsigned long flags;
	bool done;

	/*
	 * Wait while there is another request in progress, but not if recovery
	 * is needed. Also indicate whether there is a request waiting to start.
	 */
	spin_lock_irqsave(&mq->lock, flags);
	if (mq->recovery_needed) {
		*err = -EBUSY;
		done = true;
	} else {
		done = !mq->rw_wait;
	}
	mq->waiting = !done;
	spin_unlock_irqrestore(&mq->lock, flags);

	return done;
}