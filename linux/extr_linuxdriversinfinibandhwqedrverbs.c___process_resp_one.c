#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rdma_cqe_responder {scalar_t__ status; scalar_t__ flags; } ;
struct qedr_qp {int /*<<< orphan*/  ibqp; int /*<<< orphan*/  id; } ;
struct qedr_dev {int dummy; } ;
struct qedr_cq {int /*<<< orphan*/  icid; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * qp; int /*<<< orphan*/  src_qp; scalar_t__ vendor_err; scalar_t__ wc_flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,struct qedr_cq*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IB_WC_GENERAL_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 scalar_t__ RDMA_CQE_RESP_STS_OK ; 
 scalar_t__ likely (int) ; 
 scalar_t__ qedr_cqe_resp_status_to_ib (scalar_t__) ; 
 scalar_t__ qedr_set_ok_cqe_resp_wc (struct rdma_cqe_responder*,struct ib_wc*) ; 

__attribute__((used)) static void __process_resp_one(struct qedr_dev *dev, struct qedr_qp *qp,
			       struct qedr_cq *cq, struct ib_wc *wc,
			       struct rdma_cqe_responder *resp, u64 wr_id)
{
	/* Must fill fields before qedr_set_ok_cqe_resp_wc() */
	wc->opcode = IB_WC_RECV;
	wc->wc_flags = 0;

	if (likely(resp->status == RDMA_CQE_RESP_STS_OK)) {
		if (qedr_set_ok_cqe_resp_wc(resp, wc))
			DP_ERR(dev,
			       "CQ %p (icid=%d) has invalid CQE responder flags=0x%x\n",
			       cq, cq->icid, resp->flags);

	} else {
		wc->status = qedr_cqe_resp_status_to_ib(resp->status);
		if (wc->status == IB_WC_GENERAL_ERR)
			DP_ERR(dev,
			       "CQ %p (icid=%d) contains an invalid CQE status %d\n",
			       cq, cq->icid, resp->status);
	}

	/* Fill the rest of the WC */
	wc->vendor_err = 0;
	wc->src_qp = qp->id;
	wc->qp = &qp->ibqp;
	wc->wr_id = wr_id;
}