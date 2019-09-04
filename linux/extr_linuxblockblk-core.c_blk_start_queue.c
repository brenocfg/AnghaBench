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
struct request_queue {int /*<<< orphan*/  mq_ops; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_STOPPED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 

void blk_start_queue(struct request_queue *q)
{
	lockdep_assert_held(q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	queue_flag_clear(QUEUE_FLAG_STOPPED, q);
	__blk_run_queue(q);
}