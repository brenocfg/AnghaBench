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
struct ocrdma_qp {int /*<<< orphan*/  ibqp; } ;
struct ocrdma_cqe {int dummy; } ;
struct ib_wc {int /*<<< orphan*/  status; int /*<<< orphan*/ * qp; scalar_t__ byte_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  is_hw_rq_empty (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  is_hw_sq_empty (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_flush_qp (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_qp_state_change (struct ocrdma_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_set_cqe_status_flushed (struct ocrdma_qp*,struct ocrdma_cqe*) ; 
 int /*<<< orphan*/  ocrdma_to_ibwc_err (int) ; 

__attribute__((used)) static bool ocrdma_update_err_cqe(struct ib_wc *ibwc, struct ocrdma_cqe *cqe,
				  struct ocrdma_qp *qp, int status)
{
	bool expand = false;

	ibwc->byte_len = 0;
	ibwc->qp = &qp->ibqp;
	ibwc->status = ocrdma_to_ibwc_err(status);

	ocrdma_flush_qp(qp);
	ocrdma_qp_state_change(qp, IB_QPS_ERR, NULL);

	/* if wqe/rqe pending for which cqe needs to be returned,
	 * trigger inflating it.
	 */
	if (!is_hw_rq_empty(qp) || !is_hw_sq_empty(qp)) {
		expand = true;
		ocrdma_set_cqe_status_flushed(qp, cqe);
	}
	return expand;
}