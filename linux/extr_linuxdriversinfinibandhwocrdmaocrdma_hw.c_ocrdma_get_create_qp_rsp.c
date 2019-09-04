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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int dbid; int max_cnt; int max_wqe_idx; } ;
struct TYPE_3__ {int dbid; int max_cnt; int max_wqe_idx; } ;
struct ocrdma_qp {int id; int max_ird; int max_ord; int dpp_enabled; TYPE_2__ rq; TYPE_1__ sq; } ;
struct ocrdma_create_qp_rsp {int qp_id; int sq_rq_id; int max_ord_ird; int dpp_response; int max_wqe_rqe; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  srq; } ;

/* Variables and functions */
 int OCRDMA_CREATE_QP_RSP_DPP_CREDITS_MASK ; 
 int OCRDMA_CREATE_QP_RSP_DPP_CREDITS_SHIFT ; 
 int OCRDMA_CREATE_QP_RSP_DPP_ENABLED_MASK ; 
 int OCRDMA_CREATE_QP_RSP_DPP_PAGE_OFFSET_MASK ; 
 int OCRDMA_CREATE_QP_RSP_DPP_PAGE_OFFSET_SHIFT ; 
 int OCRDMA_CREATE_QP_RSP_MAX_IRD_MASK ; 
 int OCRDMA_CREATE_QP_RSP_MAX_ORD_SHIFT ; 
 int OCRDMA_CREATE_QP_RSP_MAX_WQE_SHIFT ; 
 int OCRDMA_CREATE_QP_RSP_QP_ID_MASK ; 
 int OCRDMA_CREATE_QP_RSP_RQ_ID_MASK ; 
 int OCRDMA_CREATE_QP_RSP_SQ_ID_SHIFT ; 

__attribute__((used)) static void ocrdma_get_create_qp_rsp(struct ocrdma_create_qp_rsp *rsp,
				     struct ocrdma_qp *qp,
				     struct ib_qp_init_attr *attrs,
				     u16 *dpp_offset, u16 *dpp_credit_lmt)
{
	u32 max_wqe_allocated, max_rqe_allocated;
	qp->id = rsp->qp_id & OCRDMA_CREATE_QP_RSP_QP_ID_MASK;
	qp->rq.dbid = rsp->sq_rq_id & OCRDMA_CREATE_QP_RSP_RQ_ID_MASK;
	qp->sq.dbid = rsp->sq_rq_id >> OCRDMA_CREATE_QP_RSP_SQ_ID_SHIFT;
	qp->max_ird = rsp->max_ord_ird & OCRDMA_CREATE_QP_RSP_MAX_IRD_MASK;
	qp->max_ord = (rsp->max_ord_ird >> OCRDMA_CREATE_QP_RSP_MAX_ORD_SHIFT);
	qp->dpp_enabled = false;
	if (rsp->dpp_response & OCRDMA_CREATE_QP_RSP_DPP_ENABLED_MASK) {
		qp->dpp_enabled = true;
		*dpp_credit_lmt = (rsp->dpp_response &
				OCRDMA_CREATE_QP_RSP_DPP_CREDITS_MASK) >>
				OCRDMA_CREATE_QP_RSP_DPP_CREDITS_SHIFT;
		*dpp_offset = (rsp->dpp_response &
				OCRDMA_CREATE_QP_RSP_DPP_PAGE_OFFSET_MASK) >>
				OCRDMA_CREATE_QP_RSP_DPP_PAGE_OFFSET_SHIFT;
	}
	max_wqe_allocated =
		rsp->max_wqe_rqe >> OCRDMA_CREATE_QP_RSP_MAX_WQE_SHIFT;
	max_wqe_allocated = 1 << max_wqe_allocated;
	max_rqe_allocated = 1 << ((u16)rsp->max_wqe_rqe);

	qp->sq.max_cnt = max_wqe_allocated;
	qp->sq.max_wqe_idx = max_wqe_allocated - 1;

	if (!attrs->srq) {
		qp->rq.max_cnt = max_rqe_allocated;
		qp->rq.max_wqe_idx = max_rqe_allocated - 1;
	}
}