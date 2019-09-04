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
struct TYPE_6__ {int send_flags; } ;
struct rxe_send_wqe {scalar_t__ status; TYPE_3__ wr; } ;
struct TYPE_5__ {int /*<<< orphan*/  task; scalar_t__ wait_fence; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct rxe_qp {scalar_t__ sq_sig_type; TYPE_2__ req; TYPE_1__ sq; int /*<<< orphan*/  scq; } ;
struct rxe_cqe {int dummy; } ;

/* Variables and functions */
 int IB_SEND_SIGNALED ; 
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  advance_consumer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_send_cqe (struct rxe_qp*,struct rxe_send_wqe*,struct rxe_cqe*) ; 
 int /*<<< orphan*/  rxe_cq_post (int /*<<< orphan*/ ,struct rxe_cqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void do_complete(struct rxe_qp *qp, struct rxe_send_wqe *wqe)
{
	struct rxe_cqe cqe;

	if ((qp->sq_sig_type == IB_SIGNAL_ALL_WR) ||
	    (wqe->wr.send_flags & IB_SEND_SIGNALED) ||
	    wqe->status != IB_WC_SUCCESS) {
		make_send_cqe(qp, wqe, &cqe);
		advance_consumer(qp->sq.queue);
		rxe_cq_post(qp->scq, &cqe, 0);
	} else {
		advance_consumer(qp->sq.queue);
	}

	/*
	 * we completed something so let req run again
	 * if it is trying to fence
	 */
	if (qp->req.wait_fence) {
		qp->req.wait_fence = 0;
		rxe_run_task(&qp->req.task, 1);
	}
}