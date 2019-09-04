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
struct request {int rq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int RQF_QUEUED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_clear_rq_complete (struct request*) ; 
 int /*<<< orphan*/  blk_delete_timer (struct request*) ; 
 int /*<<< orphan*/  blk_queue_end_tag (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_queued_rq (struct request*) ; 
 int /*<<< orphan*/  elv_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_requeue (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  trace_block_rq_requeue (struct request_queue*,struct request*) ; 

void blk_requeue_request(struct request_queue *q, struct request *rq)
{
	lockdep_assert_held(q->queue_lock);
	WARN_ON_ONCE(q->mq_ops);

	blk_delete_timer(rq);
	blk_clear_rq_complete(rq);
	trace_block_rq_requeue(q, rq);
	rq_qos_requeue(q, rq);

	if (rq->rq_flags & RQF_QUEUED)
		blk_queue_end_tag(q, rq);

	BUG_ON(blk_queued_rq(rq));

	elv_requeue_request(q, rq);
}