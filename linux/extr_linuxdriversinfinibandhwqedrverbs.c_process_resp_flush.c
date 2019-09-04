#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {scalar_t__ wqe_cons; size_t cons; int /*<<< orphan*/  pbl; } ;
struct qedr_qp {TYPE_2__ rq; TYPE_1__* rqe_wr_id; int /*<<< orphan*/  ibqp; int /*<<< orphan*/  id; } ;
struct qedr_cq {int dummy; } ;
struct ib_wc {int /*<<< orphan*/ * qp; int /*<<< orphan*/  wr_id; scalar_t__ byte_len; int /*<<< orphan*/  src_qp; scalar_t__ wc_flags; scalar_t__ vendor_err; int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  qed_chain_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedr_inc_sw_cons (TYPE_2__*) ; 

__attribute__((used)) static int process_resp_flush(struct qedr_qp *qp, struct qedr_cq *cq,
			      int num_entries, struct ib_wc *wc, u16 hw_cons)
{
	u16 cnt = 0;

	while (num_entries && qp->rq.wqe_cons != hw_cons) {
		/* fill WC */
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->vendor_err = 0;
		wc->wc_flags = 0;
		wc->src_qp = qp->id;
		wc->byte_len = 0;
		wc->wr_id = qp->rqe_wr_id[qp->rq.cons].wr_id;
		wc->qp = &qp->ibqp;
		num_entries--;
		wc++;
		cnt++;
		while (qp->rqe_wr_id[qp->rq.cons].wqe_size--)
			qed_chain_consume(&qp->rq.pbl);
		qedr_inc_sw_cons(&qp->rq);
	}

	return cnt;
}