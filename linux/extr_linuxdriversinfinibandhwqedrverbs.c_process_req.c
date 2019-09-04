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
typedef  scalar_t__ u16 ;
struct TYPE_8__ {scalar_t__ wqe_cons; size_t cons; int /*<<< orphan*/  pbl; } ;
struct qedr_qp {TYPE_4__ sq; TYPE_3__* wqe_wr_id; int /*<<< orphan*/  ibqp; int /*<<< orphan*/  id; } ;
struct qedr_dev {int dummy; } ;
struct qedr_cq {int dummy; } ;
struct ib_wc {int status; int opcode; int byte_len; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * qp; int /*<<< orphan*/  src_qp; scalar_t__ wc_flags; scalar_t__ vendor_err; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_7__ {int opcode; int bytes_len; int /*<<< orphan*/  wqe_size; TYPE_2__* mr; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  signaled; } ;
struct TYPE_5__ {int /*<<< orphan*/  completed; } ;
struct TYPE_6__ {TYPE_1__ info; } ;

/* Variables and functions */
#define  IB_WC_COMP_SWAP 133 
#define  IB_WC_FETCH_ADD 132 
#define  IB_WC_RDMA_READ 131 
#define  IB_WC_RDMA_WRITE 130 
#define  IB_WC_REG_MR 129 
#define  IB_WC_SEND 128 
 int /*<<< orphan*/  qed_chain_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedr_chk_if_fmr (struct qedr_qp*) ; 
 int /*<<< orphan*/  qedr_inc_sw_cons (TYPE_4__*) ; 

__attribute__((used)) static int process_req(struct qedr_dev *dev, struct qedr_qp *qp,
		       struct qedr_cq *cq, int num_entries,
		       struct ib_wc *wc, u16 hw_cons, enum ib_wc_status status,
		       int force)
{
	u16 cnt = 0;

	while (num_entries && qp->sq.wqe_cons != hw_cons) {
		if (!qp->wqe_wr_id[qp->sq.cons].signaled && !force) {
			qedr_chk_if_fmr(qp);
			/* skip WC */
			goto next_cqe;
		}

		/* fill WC */
		wc->status = status;
		wc->vendor_err = 0;
		wc->wc_flags = 0;
		wc->src_qp = qp->id;
		wc->qp = &qp->ibqp;

		wc->wr_id = qp->wqe_wr_id[qp->sq.cons].wr_id;
		wc->opcode = qp->wqe_wr_id[qp->sq.cons].opcode;

		switch (wc->opcode) {
		case IB_WC_RDMA_WRITE:
			wc->byte_len = qp->wqe_wr_id[qp->sq.cons].bytes_len;
			break;
		case IB_WC_COMP_SWAP:
		case IB_WC_FETCH_ADD:
			wc->byte_len = 8;
			break;
		case IB_WC_REG_MR:
			qp->wqe_wr_id[qp->sq.cons].mr->info.completed++;
			break;
		case IB_WC_RDMA_READ:
		case IB_WC_SEND:
			wc->byte_len = qp->wqe_wr_id[qp->sq.cons].bytes_len;
			break;
		default:
			break;
		}

		num_entries--;
		wc++;
		cnt++;
next_cqe:
		while (qp->wqe_wr_id[qp->sq.cons].wqe_size--)
			qed_chain_consume(&qp->sq.pbl);
		qedr_inc_sw_cons(&qp->sq);
	}

	return cnt;
}