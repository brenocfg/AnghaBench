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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ocrdma_qp {int dpp_enabled; } ;
struct ocrdma_pd {int /*<<< orphan*/  num_dpp_qp; } ;
struct ocrdma_create_qp_req {int dpp_credits_cqid; int /*<<< orphan*/  max_sge_recv_flags; } ;

/* Variables and functions */
 int OCRDMA_CREATE_QP_REQ_DPP_CREDIT_LIMIT ; 
 int OCRDMA_CREATE_QP_REQ_DPP_CREDIT_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK ; 

__attribute__((used)) static void ocrdma_set_create_qp_dpp_cmd(struct ocrdma_create_qp_req *cmd,
					 struct ocrdma_pd *pd,
					 struct ocrdma_qp *qp,
					 u8 enable_dpp_cq, u16 dpp_cq_id)
{
	pd->num_dpp_qp--;
	qp->dpp_enabled = true;
	cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK;
	if (!enable_dpp_cq)
		return;
	cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK;
	cmd->dpp_credits_cqid = dpp_cq_id;
	cmd->dpp_credits_cqid |= OCRDMA_CREATE_QP_REQ_DPP_CREDIT_LIMIT <<
					OCRDMA_CREATE_QP_REQ_DPP_CREDIT_SHIFT;
}