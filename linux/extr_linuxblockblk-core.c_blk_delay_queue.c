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
struct request_queue {int /*<<< orphan*/  delay_work; int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  kblockd_workqueue ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blk_delay_queue(struct request_queue *q, unsigned long msecs)
{
	lockdep_assert_held(q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	if (likely(!blk_queue_dead(q)))
		queue_delayed_work(kblockd_workqueue, &q->delay_work,
				   msecs_to_jiffies(msecs));
}