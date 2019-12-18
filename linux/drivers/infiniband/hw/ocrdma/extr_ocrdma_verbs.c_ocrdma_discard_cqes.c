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
typedef  int u32 ;
struct TYPE_8__ {int max_wqe_idx; } ;
struct ocrdma_qp {int id; TYPE_4__ rq; TYPE_3__* srq; TYPE_4__ sq; } ;
struct TYPE_6__ {int qpn; } ;
struct TYPE_5__ {int /*<<< orphan*/  buftag_qpn; } ;
struct ocrdma_cqe {TYPE_2__ cmn; TYPE_1__ rq; } ;
struct ocrdma_cq {int getp; int max_hw_cqe; int /*<<< orphan*/  cq_lock; struct ocrdma_cqe* va; } ;
struct TYPE_7__ {int /*<<< orphan*/  q_lock; TYPE_4__ rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCRDMA_CQE_BUFTAG_SHIFT ; 
 int OCRDMA_CQE_QPN_MASK ; 
 scalar_t__ is_cqe_for_sq (struct ocrdma_cqe*) ; 
 scalar_t__ is_hw_rq_empty (struct ocrdma_qp*) ; 
 scalar_t__ is_hw_sq_empty (struct ocrdma_qp*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_hwq_inc_tail (TYPE_4__*) ; 
 int /*<<< orphan*/  ocrdma_srq_toggle_bit (TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ocrdma_discard_cqes(struct ocrdma_qp *qp, struct ocrdma_cq *cq)
{
	unsigned long cq_flags;
	unsigned long flags;
	int discard_cnt = 0;
	u32 cur_getp, stop_getp;
	struct ocrdma_cqe *cqe;
	u32 qpn = 0, wqe_idx = 0;

	spin_lock_irqsave(&cq->cq_lock, cq_flags);

	/* traverse through the CQEs in the hw CQ,
	 * find the matching CQE for a given qp,
	 * mark the matching one discarded by clearing qpn.
	 * ring the doorbell in the poll_cq() as
	 * we don't complete out of order cqe.
	 */

	cur_getp = cq->getp;
	/* find upto when do we reap the cq. */
	stop_getp = cur_getp;
	do {
		if (is_hw_sq_empty(qp) && (!qp->srq && is_hw_rq_empty(qp)))
			break;

		cqe = cq->va + cur_getp;
		/* if (a) done reaping whole hw cq, or
		 *    (b) qp_xq becomes empty.
		 * then exit
		 */
		qpn = cqe->cmn.qpn & OCRDMA_CQE_QPN_MASK;
		/* if previously discarded cqe found, skip that too. */
		/* check for matching qp */
		if (qpn == 0 || qpn != qp->id)
			goto skip_cqe;

		if (is_cqe_for_sq(cqe)) {
			ocrdma_hwq_inc_tail(&qp->sq);
		} else {
			if (qp->srq) {
				wqe_idx = (le32_to_cpu(cqe->rq.buftag_qpn) >>
					OCRDMA_CQE_BUFTAG_SHIFT) &
					qp->srq->rq.max_wqe_idx;
				BUG_ON(wqe_idx < 1);
				spin_lock_irqsave(&qp->srq->q_lock, flags);
				ocrdma_hwq_inc_tail(&qp->srq->rq);
				ocrdma_srq_toggle_bit(qp->srq, wqe_idx - 1);
				spin_unlock_irqrestore(&qp->srq->q_lock, flags);

			} else {
				ocrdma_hwq_inc_tail(&qp->rq);
			}
		}
		/* mark cqe discarded so that it is not picked up later
		 * in the poll_cq().
		 */
		discard_cnt += 1;
		cqe->cmn.qpn = 0;
skip_cqe:
		cur_getp = (cur_getp + 1) % cq->max_hw_cqe;
	} while (cur_getp != stop_getp);
	spin_unlock_irqrestore(&cq->cq_lock, cq_flags);
}