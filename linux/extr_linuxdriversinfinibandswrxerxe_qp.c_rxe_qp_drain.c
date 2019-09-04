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
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  task; } ;
struct TYPE_6__ {int /*<<< orphan*/  task; } ;
struct TYPE_4__ {scalar_t__ queue; } ;
struct rxe_qp {TYPE_2__ req; TYPE_3__ comp; TYPE_1__ sq; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ QP_STATE_DRAIN ; 
 scalar_t__ QP_STATE_DRAINED ; 
 int /*<<< orphan*/  __rxe_do_task (int /*<<< orphan*/ *) ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rxe_qp_drain(struct rxe_qp *qp)
{
	if (qp->sq.queue) {
		if (qp->req.state != QP_STATE_DRAINED) {
			qp->req.state = QP_STATE_DRAIN;
			if (qp_type(qp) == IB_QPT_RC)
				rxe_run_task(&qp->comp.task, 1);
			else
				__rxe_do_task(&qp->comp.task);
			rxe_run_task(&qp->req.task, 1);
		}
	}
}