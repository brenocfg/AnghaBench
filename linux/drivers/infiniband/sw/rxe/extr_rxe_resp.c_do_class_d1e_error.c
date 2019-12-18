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
struct TYPE_6__ {int drop_msg; int opcode; int /*<<< orphan*/ * mr; TYPE_2__* wqe; int /*<<< orphan*/  status; } ;
struct rxe_qp {TYPE_3__ resp; scalar_t__ srq; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;
struct TYPE_4__ {scalar_t__ sge_offset; scalar_t__ cur_sge; int /*<<< orphan*/  length; int /*<<< orphan*/  resid; } ;
struct TYPE_5__ {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_REM_INV_REQ_ERR ; 
 int RESPST_CLEANUP ; 
 int RESPST_COMPLETE ; 
 int /*<<< orphan*/  rxe_drop_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum resp_states do_class_d1e_error(struct rxe_qp *qp)
{
	/* UC */
	if (qp->srq) {
		/* Class E */
		qp->resp.drop_msg = 1;
		if (qp->resp.wqe) {
			qp->resp.status = IB_WC_REM_INV_REQ_ERR;
			return RESPST_COMPLETE;
		} else {
			return RESPST_CLEANUP;
		}
	} else {
		/* Class D1. This packet may be the start of a
		 * new message and could be valid. The previous
		 * message is invalid and ignored. reset the
		 * recv wr to its original state
		 */
		if (qp->resp.wqe) {
			qp->resp.wqe->dma.resid = qp->resp.wqe->dma.length;
			qp->resp.wqe->dma.cur_sge = 0;
			qp->resp.wqe->dma.sge_offset = 0;
			qp->resp.opcode = -1;
		}

		if (qp->resp.mr) {
			rxe_drop_ref(qp->resp.mr);
			qp->resp.mr = NULL;
		}

		return RESPST_CLEANUP;
	}
}