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
struct request_queue {struct elevator_queue* elevator; } ;
struct request {int dummy; } ;
struct elevator_queue {TYPE_3__* type; int /*<<< orphan*/  uses_mq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* elevator_allow_rq_merge_fn ) (struct request_queue*,struct request*,struct request*) ;} ;
struct TYPE_5__ {TYPE_1__ sq; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_put_request (struct request_queue*,struct request*) ; 
 struct request* attempt_merge (struct request_queue*,struct request*,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*,struct request*) ; 

int blk_attempt_req_merge(struct request_queue *q, struct request *rq,
			  struct request *next)
{
	struct elevator_queue *e = q->elevator;
	struct request *free;

	if (!e->uses_mq && e->type->ops.sq.elevator_allow_rq_merge_fn)
		if (!e->type->ops.sq.elevator_allow_rq_merge_fn(q, rq, next))
			return 0;

	free = attempt_merge(q, rq, next);
	if (free) {
		__blk_put_request(q, free);
		return 1;
	}

	return 0;
}