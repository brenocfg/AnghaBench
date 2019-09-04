#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct elevator_queue* elevator; } ;
struct request {int dummy; } ;
struct elevator_queue {TYPE_2__* type; scalar_t__ uses_mq; } ;
struct TYPE_5__ {struct request* (* elevator_latter_req_fn ) (struct request_queue*,struct request*) ;} ;
struct TYPE_7__ {struct request* (* next_request ) (struct request_queue*,struct request*) ;} ;
struct TYPE_8__ {TYPE_1__ sq; TYPE_3__ mq; } ;
struct TYPE_6__ {TYPE_4__ ops; } ;

/* Variables and functions */
 struct request* stub1 (struct request_queue*,struct request*) ; 
 struct request* stub2 (struct request_queue*,struct request*) ; 

struct request *elv_latter_request(struct request_queue *q, struct request *rq)
{
	struct elevator_queue *e = q->elevator;

	if (e->uses_mq && e->type->ops.mq.next_request)
		return e->type->ops.mq.next_request(q, rq);
	else if (!e->uses_mq && e->type->ops.sq.elevator_latter_req_fn)
		return e->type->ops.sq.elevator_latter_req_fn(q, rq);

	return NULL;
}