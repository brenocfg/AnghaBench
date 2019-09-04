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
struct request_queue {int /*<<< orphan*/ * in_flight; } ;
struct request {int rq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELEVATOR_INSERT_REQUEUE ; 
 int RQF_SORTED ; 
 int RQF_STARTED ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_account_rq (struct request*) ; 
 int /*<<< orphan*/  blk_pm_requeue_request (struct request*) ; 
 int /*<<< orphan*/  elv_deactivate_rq (struct request_queue*,struct request*) ; 
 size_t rq_is_sync (struct request*) ; 

void elv_requeue_request(struct request_queue *q, struct request *rq)
{
	/*
	 * it already went through dequeue, we need to decrement the
	 * in_flight count again
	 */
	if (blk_account_rq(rq)) {
		q->in_flight[rq_is_sync(rq)]--;
		if (rq->rq_flags & RQF_SORTED)
			elv_deactivate_rq(q, rq);
	}

	rq->rq_flags &= ~RQF_STARTED;

	blk_pm_requeue_request(rq);

	__elv_add_request(q, rq, ELEVATOR_INSERT_REQUEUE);
}