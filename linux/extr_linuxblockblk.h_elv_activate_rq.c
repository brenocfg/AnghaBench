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
struct elevator_queue {TYPE_3__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* elevator_activate_req_fn ) (struct request_queue*,struct request*) ;} ;
struct TYPE_5__ {TYPE_1__ sq; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*) ; 

__attribute__((used)) static inline void elv_activate_rq(struct request_queue *q, struct request *rq)
{
	struct elevator_queue *e = q->elevator;

	if (e->type->ops.sq.elevator_activate_req_fn)
		e->type->ops.sq.elevator_activate_req_fn(q, rq);
}