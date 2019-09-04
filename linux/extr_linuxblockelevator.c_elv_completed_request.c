#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/ * in_flight; struct elevator_queue* elevator; } ;
struct request {int rq_flags; } ;
struct elevator_queue {TYPE_2__* type; int /*<<< orphan*/  uses_mq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* elevator_completed_req_fn ) (struct request_queue*,struct request*) ;} ;
struct TYPE_6__ {TYPE_1__ sq; } ;
struct TYPE_5__ {TYPE_3__ ops; } ;

/* Variables and functions */
 int RQF_SORTED ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_account_rq (struct request*) ; 
 size_t rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*) ; 

void elv_completed_request(struct request_queue *q, struct request *rq)
{
	struct elevator_queue *e = q->elevator;

	if (WARN_ON_ONCE(e->uses_mq))
		return;

	/*
	 * request is released from the driver, io must be done
	 */
	if (blk_account_rq(rq)) {
		q->in_flight[rq_is_sync(rq)]--;
		if ((rq->rq_flags & RQF_SORTED) &&
		    e->type->ops.sq.elevator_completed_req_fn)
			e->type->ops.sq.elevator_completed_req_fn(q, rq);
	}
}