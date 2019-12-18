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
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {int /*<<< orphan*/  cons; int /*<<< orphan*/  prod; int /*<<< orphan*/  db; TYPE_1__ db_data; } ;
struct qedr_qp {TYPE_2__ sq; TYPE_2__ rq; int /*<<< orphan*/  prev_wqe_size; } ;
struct qedr_dev {int /*<<< orphan*/  ibdev; } ;
typedef  enum qed_roce_qp_state { ____Placeholder_qed_roce_qp_state } qed_roce_qp_state ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qedr_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  QED_ROCE_QP_STATE_ERR 133 
#define  QED_ROCE_QP_STATE_INIT 132 
#define  QED_ROCE_QP_STATE_RESET 131 
#define  QED_ROCE_QP_STATE_RTR 130 
#define  QED_ROCE_QP_STATE_RTS 129 
#define  QED_ROCE_QP_STATE_SQD 128 
 int /*<<< orphan*/  qedr_reset_qp_hwq_info (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_protocol_roce (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedr_update_qp_state(struct qedr_dev *dev,
				struct qedr_qp *qp,
				enum qed_roce_qp_state cur_state,
				enum qed_roce_qp_state new_state)
{
	int status = 0;

	if (new_state == cur_state)
		return 0;

	switch (cur_state) {
	case QED_ROCE_QP_STATE_RESET:
		switch (new_state) {
		case QED_ROCE_QP_STATE_INIT:
			qp->prev_wqe_size = 0;
			qedr_reset_qp_hwq_info(&qp->sq);
			qedr_reset_qp_hwq_info(&qp->rq);
			break;
		default:
			status = -EINVAL;
			break;
		}
		break;
	case QED_ROCE_QP_STATE_INIT:
		switch (new_state) {
		case QED_ROCE_QP_STATE_RTR:
			/* Update doorbell (in case post_recv was
			 * done before move to RTR)
			 */

			if (rdma_protocol_roce(&dev->ibdev, 1)) {
				writel(qp->rq.db_data.raw, qp->rq.db);
			}
			break;
		case QED_ROCE_QP_STATE_ERR:
			break;
		default:
			/* Invalid state change. */
			status = -EINVAL;
			break;
		}
		break;
	case QED_ROCE_QP_STATE_RTR:
		/* RTR->XXX */
		switch (new_state) {
		case QED_ROCE_QP_STATE_RTS:
			break;
		case QED_ROCE_QP_STATE_ERR:
			break;
		default:
			/* Invalid state change. */
			status = -EINVAL;
			break;
		}
		break;
	case QED_ROCE_QP_STATE_RTS:
		/* RTS->XXX */
		switch (new_state) {
		case QED_ROCE_QP_STATE_SQD:
			break;
		case QED_ROCE_QP_STATE_ERR:
			break;
		default:
			/* Invalid state change. */
			status = -EINVAL;
			break;
		}
		break;
	case QED_ROCE_QP_STATE_SQD:
		/* SQD->XXX */
		switch (new_state) {
		case QED_ROCE_QP_STATE_RTS:
		case QED_ROCE_QP_STATE_ERR:
			break;
		default:
			/* Invalid state change. */
			status = -EINVAL;
			break;
		}
		break;
	case QED_ROCE_QP_STATE_ERR:
		/* ERR->XXX */
		switch (new_state) {
		case QED_ROCE_QP_STATE_RESET:
			if ((qp->rq.prod != qp->rq.cons) ||
			    (qp->sq.prod != qp->sq.cons)) {
				DP_NOTICE(dev,
					  "Error->Reset with rq/sq not empty rq.prod=%x rq.cons=%x sq.prod=%x sq.cons=%x\n",
					  qp->rq.prod, qp->rq.cons, qp->sq.prod,
					  qp->sq.cons);
				status = -EINVAL;
			}
			break;
		default:
			status = -EINVAL;
			break;
		}
		break;
	default:
		status = -EINVAL;
		break;
	}

	return status;
}