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
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct TYPE_4__ {scalar_t__ opcode; int /*<<< orphan*/  wr_id; } ;
struct rxe_send_wqe {TYPE_2__ dma; TYPE_1__ wr; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp_num; } ;
struct rxe_qp {TYPE_3__ ibqp; int /*<<< orphan*/  is_user; } ;
struct ib_uverbs_wc {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  byte_len; void* wc_flags; void* opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;
struct ib_wc {TYPE_3__* qp; int /*<<< orphan*/  byte_len; void* wc_flags; void* opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;
struct rxe_cqe {struct ib_uverbs_wc uibwc; struct ib_wc ibwc; } ;

/* Variables and functions */
 void* IB_WC_WITH_IMM ; 
 scalar_t__ IB_WR_RDMA_WRITE_WITH_IMM ; 
 scalar_t__ IB_WR_SEND_WITH_IMM ; 
 int /*<<< orphan*/  memset (struct rxe_cqe*,int /*<<< orphan*/ ,int) ; 
 void* wr_to_wc_opcode (scalar_t__) ; 

__attribute__((used)) static void make_send_cqe(struct rxe_qp *qp, struct rxe_send_wqe *wqe,
			  struct rxe_cqe *cqe)
{
	memset(cqe, 0, sizeof(*cqe));

	if (!qp->is_user) {
		struct ib_wc		*wc	= &cqe->ibwc;

		wc->wr_id		= wqe->wr.wr_id;
		wc->status		= wqe->status;
		wc->opcode		= wr_to_wc_opcode(wqe->wr.opcode);
		if (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
		    wqe->wr.opcode == IB_WR_SEND_WITH_IMM)
			wc->wc_flags = IB_WC_WITH_IMM;
		wc->byte_len		= wqe->dma.length;
		wc->qp			= &qp->ibqp;
	} else {
		struct ib_uverbs_wc	*uwc	= &cqe->uibwc;

		uwc->wr_id		= wqe->wr.wr_id;
		uwc->status		= wqe->status;
		uwc->opcode		= wr_to_wc_opcode(wqe->wr.opcode);
		if (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
		    wqe->wr.opcode == IB_WR_SEND_WITH_IMM)
			uwc->wc_flags = IB_WC_WITH_IMM;
		uwc->byte_len		= wqe->dma.length;
		uwc->qp_num		= qp->ibqp.qp_num;
	}
}