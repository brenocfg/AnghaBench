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
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  raw; TYPE_2__ data; } ;
struct TYPE_8__ {size_t prod; int /*<<< orphan*/  db; TYPE_3__ db_data; } ;
struct qedr_qp {scalar_t__ qp_type; scalar_t__ state; int /*<<< orphan*/  q_lock; TYPE_4__ sq; TYPE_1__* wqe_wr_id; int /*<<< orphan*/  icid; } ;
struct qedr_dev {int /*<<< orphan*/  ibdev; } ;
struct ib_send_wr {struct ib_send_wr* next; int /*<<< orphan*/  wr_id; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ IB_QPT_GSI ; 
 int /*<<< orphan*/  QEDR_MSG_CQ ; 
 scalar_t__ QED_ROCE_QP_STATE_ERR ; 
 scalar_t__ QED_ROCE_QP_STATE_RTS ; 
 scalar_t__ QED_ROCE_QP_STATE_SQD ; 
 int __qedr_post_send (struct ib_qp*,struct ib_send_wr const*,struct ib_send_wr const**) ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_qp* get_qedr_qp (struct ib_qp*) ; 
 int qedr_gsi_post_send (struct ib_qp*,struct ib_send_wr const*,struct ib_send_wr const**) ; 
 int /*<<< orphan*/  qedr_inc_sw_prod (TYPE_4__*) ; 
 scalar_t__ rdma_protocol_roce (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qedr_post_send(struct ib_qp *ibqp, const struct ib_send_wr *wr,
		   const struct ib_send_wr **bad_wr)
{
	struct qedr_dev *dev = get_qedr_dev(ibqp->device);
	struct qedr_qp *qp = get_qedr_qp(ibqp);
	unsigned long flags;
	int rc = 0;

	*bad_wr = NULL;

	if (qp->qp_type == IB_QPT_GSI)
		return qedr_gsi_post_send(ibqp, wr, bad_wr);

	spin_lock_irqsave(&qp->q_lock, flags);

	if (rdma_protocol_roce(&dev->ibdev, 1)) {
		if ((qp->state != QED_ROCE_QP_STATE_RTS) &&
		    (qp->state != QED_ROCE_QP_STATE_ERR) &&
		    (qp->state != QED_ROCE_QP_STATE_SQD)) {
			spin_unlock_irqrestore(&qp->q_lock, flags);
			*bad_wr = wr;
			DP_DEBUG(dev, QEDR_MSG_CQ,
				 "QP in wrong state! QP icid=0x%x state %d\n",
				 qp->icid, qp->state);
			return -EINVAL;
		}
	}

	while (wr) {
		rc = __qedr_post_send(ibqp, wr, bad_wr);
		if (rc)
			break;

		qp->wqe_wr_id[qp->sq.prod].wr_id = wr->wr_id;

		qedr_inc_sw_prod(&qp->sq);

		qp->sq.db_data.data.value++;

		wr = wr->next;
	}

	/* Trigger doorbell
	 * If there was a failure in the first WR then it will be triggered in
	 * vane. However this is not harmful (as long as the producer value is
	 * unchanged). For performance reasons we avoid checking for this
	 * redundant doorbell.
	 *
	 * qp->wqe_wr_id is accessed during qedr_poll_cq, as
	 * soon as we give the doorbell, we could get a completion
	 * for this wr, therefore we need to make sure that the
	 * memory is updated before giving the doorbell.
	 * During qedr_poll_cq, rmb is called before accessing the
	 * cqe. This covers for the smp_rmb as well.
	 */
	smp_wmb();
	writel(qp->sq.db_data.raw, qp->sq.db);

	spin_unlock_irqrestore(&qp->q_lock, flags);

	return rc;
}