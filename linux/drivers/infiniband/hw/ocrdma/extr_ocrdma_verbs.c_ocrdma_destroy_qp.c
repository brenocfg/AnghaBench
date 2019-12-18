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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/  len; scalar_t__ pa; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; scalar_t__ pa; } ;
struct ocrdma_qp {scalar_t__ state; struct ocrdma_qp* rqe_wr_id_tbl; struct ocrdma_qp* wqe_wr_id_tbl; TYPE_2__ rq; int /*<<< orphan*/  srq; TYPE_1__ sq; TYPE_3__* rq_cq; TYPE_3__* sq_cq; struct ocrdma_pd* pd; } ;
struct ocrdma_pd {scalar_t__ uctx; } ;
struct ocrdma_dev {int /*<<< orphan*/  dev_lock; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  cq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int IB_QP_STATE ; 
 scalar_t__ OCRDMA_QPS_RST ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ocrdma_modify_qp (struct ib_qp*,struct ib_qp_attr*,int) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_qp* get_ocrdma_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_del_flush_qp (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_del_mmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_del_qpn_map (struct ocrdma_dev*,struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_discard_cqes (struct ocrdma_qp*,TYPE_3__*) ; 
 int /*<<< orphan*/  ocrdma_mbx_destroy_qp (struct ocrdma_dev*,struct ocrdma_qp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ocrdma_destroy_qp(struct ib_qp *ibqp, struct ib_udata *udata)
{
	struct ocrdma_pd *pd;
	struct ocrdma_qp *qp;
	struct ocrdma_dev *dev;
	struct ib_qp_attr attrs;
	int attr_mask;
	unsigned long flags;

	qp = get_ocrdma_qp(ibqp);
	dev = get_ocrdma_dev(ibqp->device);

	pd = qp->pd;

	/* change the QP state to ERROR */
	if (qp->state != OCRDMA_QPS_RST) {
		attrs.qp_state = IB_QPS_ERR;
		attr_mask = IB_QP_STATE;
		_ocrdma_modify_qp(ibqp, &attrs, attr_mask);
	}
	/* ensure that CQEs for newly created QP (whose id may be same with
	 * one which just getting destroyed are same), dont get
	 * discarded until the old CQEs are discarded.
	 */
	mutex_lock(&dev->dev_lock);
	(void) ocrdma_mbx_destroy_qp(dev, qp);

	/*
	 * acquire CQ lock while destroy is in progress, in order to
	 * protect against proessing in-flight CQEs for this QP.
	 */
	spin_lock_irqsave(&qp->sq_cq->cq_lock, flags);
	if (qp->rq_cq && (qp->rq_cq != qp->sq_cq)) {
		spin_lock(&qp->rq_cq->cq_lock);
		ocrdma_del_qpn_map(dev, qp);
		spin_unlock(&qp->rq_cq->cq_lock);
	} else {
		ocrdma_del_qpn_map(dev, qp);
	}
	spin_unlock_irqrestore(&qp->sq_cq->cq_lock, flags);

	if (!pd->uctx) {
		ocrdma_discard_cqes(qp, qp->sq_cq);
		ocrdma_discard_cqes(qp, qp->rq_cq);
	}
	mutex_unlock(&dev->dev_lock);

	if (pd->uctx) {
		ocrdma_del_mmap(pd->uctx, (u64) qp->sq.pa,
				PAGE_ALIGN(qp->sq.len));
		if (!qp->srq)
			ocrdma_del_mmap(pd->uctx, (u64) qp->rq.pa,
					PAGE_ALIGN(qp->rq.len));
	}

	ocrdma_del_flush_qp(qp);

	kfree(qp->wqe_wr_id_tbl);
	kfree(qp->rqe_wr_id_tbl);
	kfree(qp);
	return 0;
}