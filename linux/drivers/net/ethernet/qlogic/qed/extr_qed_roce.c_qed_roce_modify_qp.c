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
typedef  int /*<<< orphan*/  u32 ;
struct qed_rdma_qp {scalar_t__ cur_state; int /*<<< orphan*/  cq_prod; } ;
struct qed_rdma_modify_qp_in_params {int /*<<< orphan*/  modify_flags; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_roce_qp_state { ____Placeholder_qed_roce_qp_state } qed_roce_qp_state ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 scalar_t__ QED_ROCE_QP_STATE_ERR ; 
 int QED_ROCE_QP_STATE_INIT ; 
 int QED_ROCE_QP_STATE_RESET ; 
 scalar_t__ QED_ROCE_QP_STATE_RTR ; 
 scalar_t__ QED_ROCE_QP_STATE_RTS ; 
 scalar_t__ QED_ROCE_QP_STATE_SQD ; 
 int qed_roce_sp_create_requester (struct qed_hwfn*,struct qed_rdma_qp*) ; 
 int qed_roce_sp_create_responder (struct qed_hwfn*,struct qed_rdma_qp*) ; 
 int qed_roce_sp_destroy_qp_requester (struct qed_hwfn*,struct qed_rdma_qp*) ; 
 int qed_roce_sp_destroy_qp_responder (struct qed_hwfn*,struct qed_rdma_qp*,int /*<<< orphan*/ *) ; 
 int qed_roce_sp_modify_requester (struct qed_hwfn*,struct qed_rdma_qp*,int,int,int /*<<< orphan*/ ) ; 
 int qed_roce_sp_modify_responder (struct qed_hwfn*,struct qed_rdma_qp*,int,int /*<<< orphan*/ ) ; 

int qed_roce_modify_qp(struct qed_hwfn *p_hwfn,
		       struct qed_rdma_qp *qp,
		       enum qed_roce_qp_state prev_state,
		       struct qed_rdma_modify_qp_in_params *params)
{
	int rc = 0;

	/* Perform additional operations according to the current state and the
	 * next state
	 */
	if (((prev_state == QED_ROCE_QP_STATE_INIT) ||
	     (prev_state == QED_ROCE_QP_STATE_RESET)) &&
	    (qp->cur_state == QED_ROCE_QP_STATE_RTR)) {
		/* Init->RTR or Reset->RTR */
		rc = qed_roce_sp_create_responder(p_hwfn, qp);
		return rc;
	} else if ((prev_state == QED_ROCE_QP_STATE_RTR) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_RTS)) {
		/* RTR-> RTS */
		rc = qed_roce_sp_create_requester(p_hwfn, qp);
		if (rc)
			return rc;

		/* Send modify responder ramrod */
		rc = qed_roce_sp_modify_responder(p_hwfn, qp, false,
						  params->modify_flags);
		return rc;
	} else if ((prev_state == QED_ROCE_QP_STATE_RTS) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_RTS)) {
		/* RTS->RTS */
		rc = qed_roce_sp_modify_responder(p_hwfn, qp, false,
						  params->modify_flags);
		if (rc)
			return rc;

		rc = qed_roce_sp_modify_requester(p_hwfn, qp, false, false,
						  params->modify_flags);
		return rc;
	} else if ((prev_state == QED_ROCE_QP_STATE_RTS) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_SQD)) {
		/* RTS->SQD */
		rc = qed_roce_sp_modify_requester(p_hwfn, qp, true, false,
						  params->modify_flags);
		return rc;
	} else if ((prev_state == QED_ROCE_QP_STATE_SQD) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_SQD)) {
		/* SQD->SQD */
		rc = qed_roce_sp_modify_responder(p_hwfn, qp, false,
						  params->modify_flags);
		if (rc)
			return rc;

		rc = qed_roce_sp_modify_requester(p_hwfn, qp, false, false,
						  params->modify_flags);
		return rc;
	} else if ((prev_state == QED_ROCE_QP_STATE_SQD) &&
		   (qp->cur_state == QED_ROCE_QP_STATE_RTS)) {
		/* SQD->RTS */
		rc = qed_roce_sp_modify_responder(p_hwfn, qp, false,
						  params->modify_flags);
		if (rc)
			return rc;

		rc = qed_roce_sp_modify_requester(p_hwfn, qp, false, false,
						  params->modify_flags);

		return rc;
	} else if (qp->cur_state == QED_ROCE_QP_STATE_ERR) {
		/* ->ERR */
		rc = qed_roce_sp_modify_responder(p_hwfn, qp, true,
						  params->modify_flags);
		if (rc)
			return rc;

		rc = qed_roce_sp_modify_requester(p_hwfn, qp, false, true,
						  params->modify_flags);
		return rc;
	} else if (qp->cur_state == QED_ROCE_QP_STATE_RESET) {
		/* Any state -> RESET */
		u32 cq_prod;

		/* Send destroy responder ramrod */
		rc = qed_roce_sp_destroy_qp_responder(p_hwfn,
						      qp,
						      &cq_prod);

		if (rc)
			return rc;

		qp->cq_prod = cq_prod;

		rc = qed_roce_sp_destroy_qp_requester(p_hwfn, qp);
	} else {
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "0\n");
	}

	return rc;
}