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
struct roce_query_qp_resp_ramrod_data {int /*<<< orphan*/  output_params_addr; } ;
struct roce_query_qp_resp_output_params {int /*<<< orphan*/  flags; int /*<<< orphan*/  psn; int /*<<< orphan*/  err_flag; } ;
struct roce_query_qp_req_ramrod_data {int /*<<< orphan*/  output_params_addr; } ;
struct roce_query_qp_req_output_params {int /*<<< orphan*/  flags; int /*<<< orphan*/  psn; int /*<<< orphan*/  err_flag; } ;
struct TYPE_6__ {struct roce_query_qp_req_ramrod_data roce_query_qp_req; struct roce_query_qp_resp_ramrod_data roce_query_qp_resp; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_sp_init_data {scalar_t__ cid; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct qed_rdma_query_qp_out_params {int draining; void* state; void* sq_psn; void* rq_psn; } ;
struct qed_rdma_qp {void* cur_state; scalar_t__ icid; void* sq_psn; int /*<<< orphan*/  req_offloaded; int /*<<< orphan*/  resp_offloaded; void* rq_psn; } ;
struct TYPE_5__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_4__* cdev; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {TYPE_3__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GET_FIELD (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 void* QED_ROCE_QP_STATE_ERR ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_ERR_FLG ; 
 int /*<<< orphan*/  ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_SQ_DRAINING_FLG ; 
 int /*<<< orphan*/  ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_ERROR_FLG ; 
 int /*<<< orphan*/  ROCE_RAMROD_QUERY_QP ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct roce_query_qp_resp_output_params*,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

int qed_roce_query_qp(struct qed_hwfn *p_hwfn,
		      struct qed_rdma_qp *qp,
		      struct qed_rdma_query_qp_out_params *out_params)
{
	struct roce_query_qp_resp_output_params *p_resp_ramrod_res;
	struct roce_query_qp_req_output_params *p_req_ramrod_res;
	struct roce_query_qp_resp_ramrod_data *p_resp_ramrod;
	struct roce_query_qp_req_ramrod_data *p_req_ramrod;
	struct qed_sp_init_data init_data;
	dma_addr_t resp_ramrod_res_phys;
	dma_addr_t req_ramrod_res_phys;
	struct qed_spq_entry *p_ent;
	bool rq_err_state;
	bool sq_err_state;
	bool sq_draining;
	int rc = -ENOMEM;

	if ((!(qp->resp_offloaded)) && (!(qp->req_offloaded))) {
		/* We can't send ramrod to the fw since this qp wasn't offloaded
		 * to the fw yet
		 */
		out_params->draining = false;
		out_params->rq_psn = qp->rq_psn;
		out_params->sq_psn = qp->sq_psn;
		out_params->state = qp->cur_state;

		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "No QPs as no offload\n");
		return 0;
	}

	if (!(qp->resp_offloaded)) {
		DP_NOTICE(p_hwfn,
			  "The responder's qp should be offloaded before requester's\n");
		return -EINVAL;
	}

	/* Send a query responder ramrod to FW to get RQ-PSN and state */
	p_resp_ramrod_res = (struct roce_query_qp_resp_output_params *)
	    dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
			       sizeof(*p_resp_ramrod_res),
			       &resp_ramrod_res_phys, GFP_KERNEL);
	if (!p_resp_ramrod_res) {
		DP_NOTICE(p_hwfn,
			  "qed query qp failed: cannot allocate memory (ramrod)\n");
		return rc;
	}

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;
	rc = qed_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_QUERY_QP,
				 PROTOCOLID_ROCE, &init_data);
	if (rc)
		goto err_resp;

	p_resp_ramrod = &p_ent->ramrod.roce_query_qp_resp;
	DMA_REGPAIR_LE(p_resp_ramrod->output_params_addr, resp_ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc)
		goto err_resp;

	out_params->rq_psn = le32_to_cpu(p_resp_ramrod_res->psn);
	rq_err_state = GET_FIELD(le32_to_cpu(p_resp_ramrod_res->err_flag),
				 ROCE_QUERY_QP_RESP_OUTPUT_PARAMS_ERROR_FLG);

	dma_free_coherent(&p_hwfn->cdev->pdev->dev, sizeof(*p_resp_ramrod_res),
			  p_resp_ramrod_res, resp_ramrod_res_phys);

	if (!(qp->req_offloaded)) {
		/* Don't send query qp for the requester */
		out_params->sq_psn = qp->sq_psn;
		out_params->draining = false;

		if (rq_err_state)
			qp->cur_state = QED_ROCE_QP_STATE_ERR;

		out_params->state = qp->cur_state;

		return 0;
	}

	/* Send a query requester ramrod to FW to get SQ-PSN and state */
	p_req_ramrod_res = (struct roce_query_qp_req_output_params *)
			   dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					      sizeof(*p_req_ramrod_res),
					      &req_ramrod_res_phys,
					      GFP_KERNEL);
	if (!p_req_ramrod_res) {
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed query qp failed: cannot allocate memory (ramrod)\n");
		return rc;
	}

	/* Get SPQ entry */
	init_data.cid = qp->icid + 1;
	rc = qed_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_QUERY_QP,
				 PROTOCOLID_ROCE, &init_data);
	if (rc)
		goto err_req;

	p_req_ramrod = &p_ent->ramrod.roce_query_qp_req;
	DMA_REGPAIR_LE(p_req_ramrod->output_params_addr, req_ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc)
		goto err_req;

	out_params->sq_psn = le32_to_cpu(p_req_ramrod_res->psn);
	sq_err_state = GET_FIELD(le32_to_cpu(p_req_ramrod_res->flags),
				 ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_ERR_FLG);
	sq_draining =
		GET_FIELD(le32_to_cpu(p_req_ramrod_res->flags),
			  ROCE_QUERY_QP_REQ_OUTPUT_PARAMS_SQ_DRAINING_FLG);

	dma_free_coherent(&p_hwfn->cdev->pdev->dev, sizeof(*p_req_ramrod_res),
			  p_req_ramrod_res, req_ramrod_res_phys);

	out_params->draining = false;

	if (rq_err_state || sq_err_state)
		qp->cur_state = QED_ROCE_QP_STATE_ERR;
	else if (sq_draining)
		out_params->draining = true;
	out_params->state = qp->cur_state;

	return 0;

err_req:
	dma_free_coherent(&p_hwfn->cdev->pdev->dev, sizeof(*p_req_ramrod_res),
			  p_req_ramrod_res, req_ramrod_res_phys);
	return rc;
err_resp:
	dma_free_coherent(&p_hwfn->cdev->pdev->dev, sizeof(*p_resp_ramrod_res),
			  p_resp_ramrod_res, resp_ramrod_res_phys);
	return rc;
}