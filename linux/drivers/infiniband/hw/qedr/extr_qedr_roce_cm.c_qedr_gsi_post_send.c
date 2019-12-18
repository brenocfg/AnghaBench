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
struct TYPE_4__ {size_t prod; } ;
struct qedr_qp {scalar_t__ state; int /*<<< orphan*/  q_lock; struct qedr_dev* dev; TYPE_2__ sq; TYPE_1__* wqe_wr_id; } ;
struct qedr_dev {int dummy; } ;
struct qed_roce_ll2_packet {int dummy; } ;
struct ib_send_wr {scalar_t__ num_sge; scalar_t__ opcode; struct ib_send_wr* next; int /*<<< orphan*/  wr_id; } ;
struct ib_qp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ IB_WR_SEND ; 
 int /*<<< orphan*/  QEDR_MSG_GSI ; 
 scalar_t__ QED_ROCE_QP_STATE_RTS ; 
 scalar_t__ RDMA_MAX_SGE_PER_SQ_WQE ; 
 struct qedr_qp* get_qedr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int qedr_gsi_build_packet (struct qedr_dev*,struct qedr_qp*,struct ib_send_wr const*,struct qed_roce_ll2_packet**) ; 
 int /*<<< orphan*/  qedr_inc_sw_prod (TYPE_2__*) ; 
 int qedr_ll2_post_tx (struct qedr_dev*,struct qed_roce_ll2_packet*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qedr_gsi_post_send(struct ib_qp *ibqp, const struct ib_send_wr *wr,
		       const struct ib_send_wr **bad_wr)
{
	struct qed_roce_ll2_packet *pkt = NULL;
	struct qedr_qp *qp = get_qedr_qp(ibqp);
	struct qedr_dev *dev = qp->dev;
	unsigned long flags;
	int rc;

	if (qp->state != QED_ROCE_QP_STATE_RTS) {
		*bad_wr = wr;
		DP_ERR(dev,
		       "gsi post recv: failed to post rx buffer. state is %d and not QED_ROCE_QP_STATE_RTS\n",
		       qp->state);
		return -EINVAL;
	}

	if (wr->num_sge > RDMA_MAX_SGE_PER_SQ_WQE) {
		DP_ERR(dev, "gsi post send: num_sge is too large (%d>%d)\n",
		       wr->num_sge, RDMA_MAX_SGE_PER_SQ_WQE);
		rc = -EINVAL;
		goto err;
	}

	if (wr->opcode != IB_WR_SEND) {
		DP_ERR(dev,
		       "gsi post send: failed due to unsupported opcode %d\n",
		       wr->opcode);
		rc = -EINVAL;
		goto err;
	}

	spin_lock_irqsave(&qp->q_lock, flags);

	rc = qedr_gsi_build_packet(dev, qp, wr, &pkt);
	if (rc) {
		spin_unlock_irqrestore(&qp->q_lock, flags);
		goto err;
	}

	rc = qedr_ll2_post_tx(dev, pkt);

	if (!rc) {
		qp->wqe_wr_id[qp->sq.prod].wr_id = wr->wr_id;
		qedr_inc_sw_prod(&qp->sq);
		DP_DEBUG(qp->dev, QEDR_MSG_GSI,
			 "gsi post send: opcode=%d, in_irq=%ld, irqs_disabled=%d, wr_id=%llx\n",
			 wr->opcode, in_irq(), irqs_disabled(), wr->wr_id);
	} else {
		DP_ERR(dev, "gsi post send: failed to transmit (rc=%d)\n", rc);
		rc = -EAGAIN;
		*bad_wr = wr;
	}

	spin_unlock_irqrestore(&qp->q_lock, flags);

	if (wr->next) {
		DP_ERR(dev,
		       "gsi post send: failed second WR. Only one WR may be passed at a time\n");
		*bad_wr = wr->next;
		rc = -EINVAL;
	}

	return rc;

err:
	*bad_wr = wr;
	return rc;
}