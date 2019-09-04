#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct io_cq {int flags; TYPE_3__* q; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* elevator_exit_icq_fn ) (struct io_cq*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* exit_icq ) (struct io_cq*) ;} ;
struct TYPE_10__ {TYPE_1__ sq; TYPE_4__ mq; } ;
struct elevator_type {TYPE_5__ ops; scalar_t__ uses_mq; } ;
struct TYPE_8__ {TYPE_2__* elevator; } ;
struct TYPE_7__ {struct elevator_type* type; } ;

/* Variables and functions */
 int ICQ_EXITED ; 
 int /*<<< orphan*/  stub1 (struct io_cq*) ; 
 int /*<<< orphan*/  stub2 (struct io_cq*) ; 

__attribute__((used)) static void ioc_exit_icq(struct io_cq *icq)
{
	struct elevator_type *et = icq->q->elevator->type;

	if (icq->flags & ICQ_EXITED)
		return;

	if (et->uses_mq && et->ops.mq.exit_icq)
		et->ops.mq.exit_icq(icq);
	else if (!et->uses_mq && et->ops.sq.elevator_exit_icq_fn)
		et->ops.sq.elevator_exit_icq_fn(icq);

	icq->flags |= ICQ_EXITED;
}