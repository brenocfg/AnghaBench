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
struct TYPE_6__ {int /*<<< orphan*/  task; void* state; } ;
struct TYPE_5__ {int /*<<< orphan*/  task; } ;
struct TYPE_7__ {int /*<<< orphan*/  task; void* state; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp_state; } ;
struct rxe_qp {TYPE_2__ req; TYPE_1__ comp; TYPE_3__ resp; TYPE_4__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_ERR ; 
 scalar_t__ IB_QPT_RC ; 
 void* QP_STATE_ERROR ; 
 int /*<<< orphan*/  __rxe_do_task (int /*<<< orphan*/ *) ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 

void rxe_qp_error(struct rxe_qp *qp)
{
	qp->req.state = QP_STATE_ERROR;
	qp->resp.state = QP_STATE_ERROR;
	qp->attr.qp_state = IB_QPS_ERR;

	/* drain work and packet queues */
	rxe_run_task(&qp->resp.task, 1);

	if (qp_type(qp) == IB_QPT_RC)
		rxe_run_task(&qp->comp.task, 1);
	else
		__rxe_do_task(&qp->comp.task);
	rxe_run_task(&qp->req.task, 1);
}