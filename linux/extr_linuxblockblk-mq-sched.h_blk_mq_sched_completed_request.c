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
struct request {TYPE_1__* q; } ;
struct elevator_queue {TYPE_4__* type; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* completed_request ) (struct request*) ;} ;
struct TYPE_7__ {TYPE_2__ mq; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {struct elevator_queue* elevator; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct request*) ; 

__attribute__((used)) static inline void blk_mq_sched_completed_request(struct request *rq)
{
	struct elevator_queue *e = rq->q->elevator;

	if (e && e->type->ops.mq.completed_request)
		e->type->ops.mq.completed_request(rq);
}