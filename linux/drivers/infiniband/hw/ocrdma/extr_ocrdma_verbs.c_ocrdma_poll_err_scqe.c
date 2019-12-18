#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ocrdma_qp {scalar_t__ sq_cq; scalar_t__ rq_cq; int /*<<< orphan*/  srq; TYPE_1__ ibqp; } ;
struct ocrdma_dev {int /*<<< orphan*/ * cqe_err_stats; } ;
struct ocrdma_cqe {int /*<<< orphan*/  flags_status_srcqpn; } ;
struct ib_wc {int dummy; } ;

/* Variables and functions */
 int OCRDMA_CQE_STATUS_MASK ; 
 int OCRDMA_CQE_STATUS_SHIFT ; 
 int OCRDMA_CQE_WR_FLUSH_ERR ; 
 int OCRDMA_MAX_CQE_ERR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hw_rq_empty (struct ocrdma_qp*) ; 
 scalar_t__ is_hw_sq_empty (struct ocrdma_qp*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ocrdma_update_err_rcqe (struct ib_wc*,struct ocrdma_cqe*,struct ocrdma_qp*,int) ; 
 int ocrdma_update_err_scqe (struct ib_wc*,struct ocrdma_cqe*,struct ocrdma_qp*,int) ; 

__attribute__((used)) static bool ocrdma_poll_err_scqe(struct ocrdma_qp *qp,
				 struct ocrdma_cqe *cqe, struct ib_wc *ibwc,
				 bool *polled, bool *stop)
{
	bool expand;
	struct ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);
	int status = (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_STATUS_MASK) >> OCRDMA_CQE_STATUS_SHIFT;
	if (status < OCRDMA_MAX_CQE_ERR)
		atomic_inc(&dev->cqe_err_stats[status]);

	/* when hw sq is empty, but rq is not empty, so we continue
	 * to keep the cqe in order to get the cq event again.
	 */
	if (is_hw_sq_empty(qp) && !is_hw_rq_empty(qp)) {
		/* when cq for rq and sq is same, it is safe to return
		 * flush cqe for RQEs.
		 */
		if (!qp->srq && (qp->sq_cq == qp->rq_cq)) {
			*polled = true;
			status = OCRDMA_CQE_WR_FLUSH_ERR;
			expand = ocrdma_update_err_rcqe(ibwc, cqe, qp, status);
		} else {
			/* stop processing further cqe as this cqe is used for
			 * triggering cq event on buddy cq of RQ.
			 * When QP is destroyed, this cqe will be removed
			 * from the cq's hardware q.
			 */
			*polled = false;
			*stop = true;
			expand = false;
		}
	} else if (is_hw_sq_empty(qp)) {
		/* Do nothing */
		expand = false;
		*polled = false;
		*stop = false;
	} else {
		*polled = true;
		expand = ocrdma_update_err_scqe(ibwc, cqe, qp, status);
	}
	return expand;
}