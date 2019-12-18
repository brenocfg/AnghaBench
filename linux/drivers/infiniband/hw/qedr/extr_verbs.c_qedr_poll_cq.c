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
union rdma_cqe {int /*<<< orphan*/  resp; int /*<<< orphan*/  req; } ;
typedef  scalar_t__ u32 ;
struct qedr_qp {int /*<<< orphan*/  ibqp; } ;
struct qedr_dev {int dummy; } ;
struct qedr_cq {scalar_t__ cq_type; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  arm_flags; scalar_t__ cq_cons; int /*<<< orphan*/  pbl; union rdma_cqe* latest_cqe; int /*<<< orphan*/  icid; scalar_t__ destroyed; } ;
struct ib_wc {int /*<<< orphan*/ * qp; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 scalar_t__ QEDR_CQ_TYPE_GSI ; 
#define  RDMA_CQE_TYPE_INVALID 131 
#define  RDMA_CQE_TYPE_REQUESTER 130 
#define  RDMA_CQE_TYPE_RESPONDER_RQ 129 
#define  RDMA_CQE_TYPE_RESPONDER_SRQ 128 
 int /*<<< orphan*/  WARN (int,char*,union rdma_cqe*) ; 
 struct qedr_qp* cqe_get_qp (union rdma_cqe*) ; 
 int cqe_get_type (union rdma_cqe*) ; 
 int /*<<< orphan*/  doorbell_cq (struct qedr_cq*,scalar_t__,int /*<<< orphan*/ ) ; 
 union rdma_cqe* get_cqe (struct qedr_cq*) ; 
 struct qedr_cq* get_qedr_cq (struct ib_cq*) ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_cqe (struct qedr_cq*,union rdma_cqe*) ; 
 scalar_t__ qed_chain_get_cons_idx_u32 (int /*<<< orphan*/ *) ; 
 int qedr_gsi_poll_cq (struct ib_cq*,int,struct ib_wc*) ; 
 int qedr_poll_cq_req (struct qedr_dev*,struct qedr_qp*,struct qedr_cq*,int,struct ib_wc*,int /*<<< orphan*/ *) ; 
 int qedr_poll_cq_resp (struct qedr_dev*,struct qedr_qp*,struct qedr_cq*,int,struct ib_wc*,int /*<<< orphan*/ *,int*) ; 
 int qedr_poll_cq_resp_srq (struct qedr_dev*,struct qedr_qp*,struct qedr_cq*,int,struct ib_wc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_consume_req_cqe (struct qedr_cq*,struct qedr_qp*,int /*<<< orphan*/ *,int*) ; 

int qedr_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct qedr_dev *dev = get_qedr_dev(ibcq->device);
	struct qedr_cq *cq = get_qedr_cq(ibcq);
	union rdma_cqe *cqe;
	u32 old_cons, new_cons;
	unsigned long flags;
	int update = 0;
	int done = 0;

	if (cq->destroyed) {
		DP_ERR(dev,
		       "warning: poll was invoked after destroy for cq %p (icid=%d)\n",
		       cq, cq->icid);
		return 0;
	}

	if (cq->cq_type == QEDR_CQ_TYPE_GSI)
		return qedr_gsi_poll_cq(ibcq, num_entries, wc);

	spin_lock_irqsave(&cq->cq_lock, flags);
	cqe = cq->latest_cqe;
	old_cons = qed_chain_get_cons_idx_u32(&cq->pbl);
	while (num_entries && is_valid_cqe(cq, cqe)) {
		struct qedr_qp *qp;
		int cnt = 0;

		/* prevent speculative reads of any field of CQE */
		rmb();

		qp = cqe_get_qp(cqe);
		if (!qp) {
			WARN(1, "Error: CQE QP pointer is NULL. CQE=%p\n", cqe);
			break;
		}

		wc->qp = &qp->ibqp;

		switch (cqe_get_type(cqe)) {
		case RDMA_CQE_TYPE_REQUESTER:
			cnt = qedr_poll_cq_req(dev, qp, cq, num_entries, wc,
					       &cqe->req);
			try_consume_req_cqe(cq, qp, &cqe->req, &update);
			break;
		case RDMA_CQE_TYPE_RESPONDER_RQ:
			cnt = qedr_poll_cq_resp(dev, qp, cq, num_entries, wc,
						&cqe->resp, &update);
			break;
		case RDMA_CQE_TYPE_RESPONDER_SRQ:
			cnt = qedr_poll_cq_resp_srq(dev, qp, cq, num_entries,
						    wc, &cqe->resp);
			update = 1;
			break;
		case RDMA_CQE_TYPE_INVALID:
		default:
			DP_ERR(dev, "Error: invalid CQE type = %d\n",
			       cqe_get_type(cqe));
		}
		num_entries -= cnt;
		wc += cnt;
		done += cnt;

		cqe = get_cqe(cq);
	}
	new_cons = qed_chain_get_cons_idx_u32(&cq->pbl);

	cq->cq_cons += new_cons - old_cons;

	if (update)
		/* doorbell notifies abount latest VALID entry,
		 * but chain already point to the next INVALID one
		 */
		doorbell_cq(cq, cq->cq_cons - 1, cq->arm_flags);

	spin_unlock_irqrestore(&cq->cq_lock, flags);
	return done;
}