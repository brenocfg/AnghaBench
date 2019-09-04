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
struct request_queue {int /*<<< orphan*/  mq_freeze_depth; int /*<<< orphan*/  mq_freeze_wq; int /*<<< orphan*/  q_usage_counter; } ;
typedef  int blk_mq_req_flags_t ;

/* Variables and functions */
 int BLK_MQ_REQ_NOWAIT ; 
 int BLK_MQ_REQ_PREEMPT ; 
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_preempt_only (struct request_queue*) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_ref_tryget_live (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int blk_queue_enter(struct request_queue *q, blk_mq_req_flags_t flags)
{
	const bool preempt = flags & BLK_MQ_REQ_PREEMPT;

	while (true) {
		bool success = false;

		rcu_read_lock();
		if (percpu_ref_tryget_live(&q->q_usage_counter)) {
			/*
			 * The code that sets the PREEMPT_ONLY flag is
			 * responsible for ensuring that that flag is globally
			 * visible before the queue is unfrozen.
			 */
			if (preempt || !blk_queue_preempt_only(q)) {
				success = true;
			} else {
				percpu_ref_put(&q->q_usage_counter);
			}
		}
		rcu_read_unlock();

		if (success)
			return 0;

		if (flags & BLK_MQ_REQ_NOWAIT)
			return -EBUSY;

		/*
		 * read pair of barrier in blk_freeze_queue_start(),
		 * we need to order reading __PERCPU_REF_DEAD flag of
		 * .q_usage_counter and reading .mq_freeze_depth or
		 * queue dying flag, otherwise the following wait may
		 * never return if the two reads are reordered.
		 */
		smp_rmb();

		wait_event(q->mq_freeze_wq,
			   (atomic_read(&q->mq_freeze_depth) == 0 &&
			    (preempt || !blk_queue_preempt_only(q))) ||
			   blk_queue_dying(q));
		if (blk_queue_dying(q))
			return -ENODEV;
	}
}