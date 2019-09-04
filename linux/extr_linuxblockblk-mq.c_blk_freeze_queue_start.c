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
struct request_queue {scalar_t__ mq_ops; int /*<<< orphan*/  q_usage_counter; int /*<<< orphan*/  mq_freeze_depth; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 

void blk_freeze_queue_start(struct request_queue *q)
{
	int freeze_depth;

	freeze_depth = atomic_inc_return(&q->mq_freeze_depth);
	if (freeze_depth == 1) {
		percpu_ref_kill(&q->q_usage_counter);
		if (q->mq_ops)
			blk_mq_run_hw_queues(q, false);
	}
}