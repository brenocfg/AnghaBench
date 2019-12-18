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
typedef  int /*<<< orphan*/  u8 ;
struct regpair {int dummy; } ;
struct TYPE_8__ {void* lo; void* hi; } ;
struct TYPE_7__ {void* lo; void* hi; } ;
struct qed_rdma_qp {int sq_num_pages; int rq_num_pages; int req_offloaded; int resp_offloaded; int e2e_flow_control_en; int qpid; int icid; int /*<<< orphan*/  stats_queue; scalar_t__ use_srq; int /*<<< orphan*/  srq_id; int /*<<< orphan*/  rq_pbl_ptr; int /*<<< orphan*/  rq_cq_id; int /*<<< orphan*/  sq_pbl_ptr; int /*<<< orphan*/  sq_cq_id; int /*<<< orphan*/  dpi; int /*<<< orphan*/  pd; int /*<<< orphan*/  fmr_and_reserved_lkey; int /*<<< orphan*/  signal_all; TYPE_4__ qp_handle_async; TYPE_3__ qp_handle; int /*<<< orphan*/  cur_state; } ;
struct qed_rdma_create_qp_out_params {int icid; int qp_id; } ;
struct qed_rdma_create_qp_in_params {int sq_num_pages; int rq_num_pages; int /*<<< orphan*/  stats_queue; int /*<<< orphan*/  srq_id; int /*<<< orphan*/  rq_pbl_ptr; int /*<<< orphan*/  rq_cq_id; int /*<<< orphan*/  sq_pbl_ptr; int /*<<< orphan*/  sq_cq_id; int /*<<< orphan*/  dpi; int /*<<< orphan*/  pd; int /*<<< orphan*/  fmr_and_reserved_lkey; int /*<<< orphan*/  signal_all; scalar_t__ use_srq; int /*<<< orphan*/  qp_handle_async_lo; int /*<<< orphan*/  qp_handle_async_hi; int /*<<< orphan*/  qp_handle_lo; int /*<<< orphan*/  qp_handle_hi; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; TYPE_2__* p_rdma_info; } ;
struct TYPE_6__ {TYPE_1__* dev; int /*<<< orphan*/  active; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_stats_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (int /*<<< orphan*/ ,char*,void*,struct qed_rdma_create_qp_in_params*,...) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IWARP_SHARED_QUEUE_PAGE_RQ_PBL_MAX_SIZE ; 
 int IWARP_SHARED_QUEUE_PAGE_SQ_PBL_MAX_SIZE ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_ROCE_QP_STATE_RESET ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_rdma_qp*) ; 
 struct qed_rdma_qp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qed_iwarp_create_qp (struct qed_hwfn*,struct qed_rdma_qp*,struct qed_rdma_create_qp_out_params*) ; 
 int qed_roce_alloc_cid (struct qed_hwfn*,int*) ; 

__attribute__((used)) static struct qed_rdma_qp *
qed_rdma_create_qp(void *rdma_cxt,
		   struct qed_rdma_create_qp_in_params *in_params,
		   struct qed_rdma_create_qp_out_params *out_params)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	struct qed_rdma_qp *qp;
	u8 max_stats_queues;
	int rc;

	if (!rdma_cxt || !in_params || !out_params ||
	    !p_hwfn->p_rdma_info->active) {
		DP_ERR(p_hwfn->cdev,
		       "qed roce create qp failed due to NULL entry (rdma_cxt=%p, in=%p, out=%p, roce_info=?\n",
		       rdma_cxt, in_params, out_params);
		return NULL;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "qed rdma create qp called with qp_handle = %08x%08x\n",
		   in_params->qp_handle_hi, in_params->qp_handle_lo);

	/* Some sanity checks... */
	max_stats_queues = p_hwfn->p_rdma_info->dev->max_stats_queues;
	if (in_params->stats_queue >= max_stats_queues) {
		DP_ERR(p_hwfn->cdev,
		       "qed rdma create qp failed due to invalid statistics queue %d. maximum is %d\n",
		       in_params->stats_queue, max_stats_queues);
		return NULL;
	}

	if (QED_IS_IWARP_PERSONALITY(p_hwfn)) {
		if (in_params->sq_num_pages * sizeof(struct regpair) >
		    IWARP_SHARED_QUEUE_PAGE_SQ_PBL_MAX_SIZE) {
			DP_NOTICE(p_hwfn->cdev,
				  "Sq num pages: %d exceeds maximum\n",
				  in_params->sq_num_pages);
			return NULL;
		}
		if (in_params->rq_num_pages * sizeof(struct regpair) >
		    IWARP_SHARED_QUEUE_PAGE_RQ_PBL_MAX_SIZE) {
			DP_NOTICE(p_hwfn->cdev,
				  "Rq num pages: %d exceeds maximum\n",
				  in_params->rq_num_pages);
			return NULL;
		}
	}

	qp = kzalloc(sizeof(*qp), GFP_KERNEL);
	if (!qp)
		return NULL;

	qp->cur_state = QED_ROCE_QP_STATE_RESET;
	qp->qp_handle.hi = cpu_to_le32(in_params->qp_handle_hi);
	qp->qp_handle.lo = cpu_to_le32(in_params->qp_handle_lo);
	qp->qp_handle_async.hi = cpu_to_le32(in_params->qp_handle_async_hi);
	qp->qp_handle_async.lo = cpu_to_le32(in_params->qp_handle_async_lo);
	qp->use_srq = in_params->use_srq;
	qp->signal_all = in_params->signal_all;
	qp->fmr_and_reserved_lkey = in_params->fmr_and_reserved_lkey;
	qp->pd = in_params->pd;
	qp->dpi = in_params->dpi;
	qp->sq_cq_id = in_params->sq_cq_id;
	qp->sq_num_pages = in_params->sq_num_pages;
	qp->sq_pbl_ptr = in_params->sq_pbl_ptr;
	qp->rq_cq_id = in_params->rq_cq_id;
	qp->rq_num_pages = in_params->rq_num_pages;
	qp->rq_pbl_ptr = in_params->rq_pbl_ptr;
	qp->srq_id = in_params->srq_id;
	qp->req_offloaded = false;
	qp->resp_offloaded = false;
	qp->e2e_flow_control_en = qp->use_srq ? false : true;
	qp->stats_queue = in_params->stats_queue;

	if (QED_IS_IWARP_PERSONALITY(p_hwfn)) {
		rc = qed_iwarp_create_qp(p_hwfn, qp, out_params);
		qp->qpid = qp->icid;
	} else {
		rc = qed_roce_alloc_cid(p_hwfn, &qp->icid);
		qp->qpid = ((0xFF << 16) | qp->icid);
	}

	if (rc) {
		kfree(qp);
		return NULL;
	}

	out_params->icid = qp->icid;
	out_params->qp_id = qp->qpid;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Create QP, rc = %d\n", rc);
	return qp;
}