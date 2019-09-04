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
typedef  int /*<<< orphan*/  u64 ;
struct rdma_cqe_responder {int dummy; } ;
struct TYPE_4__ {size_t cons; int /*<<< orphan*/  pbl; } ;
struct qedr_qp {TYPE_2__ rq; TYPE_1__* rqe_wr_id; } ;
struct qedr_dev {int dummy; } ;
struct qedr_cq {int dummy; } ;
struct ib_wc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  __process_resp_one (struct qedr_dev*,struct qedr_qp*,struct qedr_cq*,struct ib_wc*,struct rdma_cqe_responder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedr_inc_sw_cons (TYPE_2__*) ; 

__attribute__((used)) static int process_resp_one(struct qedr_dev *dev, struct qedr_qp *qp,
			    struct qedr_cq *cq, struct ib_wc *wc,
			    struct rdma_cqe_responder *resp)
{
	u64 wr_id = qp->rqe_wr_id[qp->rq.cons].wr_id;

	__process_resp_one(dev, qp, cq, wc, resp, wr_id);

	while (qp->rqe_wr_id[qp->rq.cons].wqe_size--)
		qed_chain_consume(&qp->rq.pbl);
	qedr_inc_sw_cons(&qp->rq);

	return 1;
}