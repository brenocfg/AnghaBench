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
struct request_queue {struct request* last_merge; struct elevator_queue* elevator; } ;
struct request {int dummy; } ;
struct elevator_queue {TYPE_4__* type; scalar_t__ uses_mq; } ;
typedef  enum elv_merge { ____Placeholder_elv_merge } elv_merge ;
struct TYPE_6__ {int /*<<< orphan*/  (* elevator_merged_fn ) (struct request_queue*,struct request*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* request_merged ) (struct request_queue*,struct request*,int) ;} ;
struct TYPE_7__ {TYPE_2__ sq; TYPE_1__ mq; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;

/* Variables and functions */
 int ELEVATOR_BACK_MERGE ; 
 int /*<<< orphan*/  elv_rqhash_reposition (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*,int) ; 
 int /*<<< orphan*/  stub2 (struct request_queue*,struct request*,int) ; 

void elv_merged_request(struct request_queue *q, struct request *rq,
		enum elv_merge type)
{
	struct elevator_queue *e = q->elevator;

	if (e->uses_mq && e->type->ops.mq.request_merged)
		e->type->ops.mq.request_merged(q, rq, type);
	else if (!e->uses_mq && e->type->ops.sq.elevator_merged_fn)
		e->type->ops.sq.elevator_merged_fn(q, rq, type);

	if (type == ELEVATOR_BACK_MERGE)
		elv_rqhash_reposition(q, rq);

	q->last_merge = rq;
}