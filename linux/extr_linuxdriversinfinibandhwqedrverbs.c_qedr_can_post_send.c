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
struct TYPE_2__ {scalar_t__ max_sges; int /*<<< orphan*/  pbl; } ;
struct qedr_qp {int err_bitmap; TYPE_1__ sq; struct qedr_dev* dev; } ;
struct qedr_dev {int dummy; } ;
struct ib_send_wr {scalar_t__ num_sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,struct qedr_qp*) ; 
 scalar_t__ QEDR_MAX_SQE_ELEMENTS_PER_SQE ; 
 int QEDR_QP_ERR_BAD_SR ; 
 int QEDR_QP_ERR_SQ_FULL ; 
 int QEDR_QP_ERR_SQ_PBL_FULL ; 
 scalar_t__ qed_chain_get_elem_left_u32 (int /*<<< orphan*/ *) ; 
 int qedr_wq_is_full (TYPE_1__*) ; 

__attribute__((used)) static inline bool qedr_can_post_send(struct qedr_qp *qp,
				      const struct ib_send_wr *wr)
{
	int wq_is_full, err_wr, pbl_is_full;
	struct qedr_dev *dev = qp->dev;

	/* prevent SQ overflow and/or processing of a bad WR */
	err_wr = wr->num_sge > qp->sq.max_sges;
	wq_is_full = qedr_wq_is_full(&qp->sq);
	pbl_is_full = qed_chain_get_elem_left_u32(&qp->sq.pbl) <
		      QEDR_MAX_SQE_ELEMENTS_PER_SQE;
	if (wq_is_full || err_wr || pbl_is_full) {
		if (wq_is_full && !(qp->err_bitmap & QEDR_QP_ERR_SQ_FULL)) {
			DP_ERR(dev,
			       "error: WQ is full. Post send on QP %p failed (this error appears only once)\n",
			       qp);
			qp->err_bitmap |= QEDR_QP_ERR_SQ_FULL;
		}

		if (err_wr && !(qp->err_bitmap & QEDR_QP_ERR_BAD_SR)) {
			DP_ERR(dev,
			       "error: WR is bad. Post send on QP %p failed (this error appears only once)\n",
			       qp);
			qp->err_bitmap |= QEDR_QP_ERR_BAD_SR;
		}

		if (pbl_is_full &&
		    !(qp->err_bitmap & QEDR_QP_ERR_SQ_PBL_FULL)) {
			DP_ERR(dev,
			       "error: WQ PBL is full. Post send on QP %p failed (this error appears only once)\n",
			       qp);
			qp->err_bitmap |= QEDR_QP_ERR_SQ_PBL_FULL;
		}
		return false;
	}
	return true;
}