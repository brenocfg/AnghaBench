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
struct request_queue {int /*<<< orphan*/  mq_freeze_wq; int /*<<< orphan*/  q_usage_counter; int /*<<< orphan*/  mq_freeze_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_reinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void blk_mq_unfreeze_queue(struct request_queue *q)
{
	int freeze_depth;

	freeze_depth = atomic_dec_return(&q->mq_freeze_depth);
	WARN_ON_ONCE(freeze_depth < 0);
	if (!freeze_depth) {
		percpu_ref_reinit(&q->q_usage_counter);
		wake_up_all(&q->mq_freeze_wq);
	}
}