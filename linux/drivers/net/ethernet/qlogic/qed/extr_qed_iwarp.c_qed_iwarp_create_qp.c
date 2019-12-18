#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_10__ {void* lo; void* hi; } ;
struct TYPE_9__ {void* opaque_fid; void* srq_idx; } ;
struct iwarp_create_qp_ramrod_data {void* physical_q1; void* physical_q0; void* dpi; void* cq_cid_for_rq; void* cq_cid_for_sq; TYPE_3__ qp_handle_for_cqe; TYPE_2__ srq_id; int /*<<< orphan*/  rq_num_pages; int /*<<< orphan*/  sq_num_pages; int /*<<< orphan*/  pd; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {struct iwarp_create_qp_ramrod_data iwarp_create_qp; } ;
struct qed_spq_entry {TYPE_1__ ramrod; } ;
struct qed_sp_init_data {int opaque_fid; int cid; int /*<<< orphan*/  comp_mode; } ;
struct TYPE_11__ {int hi; int lo; } ;
struct qed_rdma_qp {int shared_queue_phys_addr; int icid; int srq_id; int sq_cq_id; int rq_cq_id; int dpi; scalar_t__ shared_queue; TYPE_4__ qp_handle; int /*<<< orphan*/  rq_num_pages; int /*<<< orphan*/  sq_num_pages; int /*<<< orphan*/  pd; int /*<<< orphan*/  use_srq; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; int /*<<< orphan*/  signal_all; int /*<<< orphan*/  fmr_and_reserved_lkey; } ;
struct qed_rdma_create_qp_out_params {int sq_pbl_phys; int rq_pbl_phys; int /*<<< orphan*/ * rq_pbl_virt; int /*<<< orphan*/ * sq_pbl_virt; } ;
struct TYPE_12__ {int opaque_fid; } ;
struct qed_hwfn {TYPE_7__* cdev; TYPE_5__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
struct TYPE_14__ {TYPE_6__* pdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP ; 
 int /*<<< orphan*/  IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG ; 
 int /*<<< orphan*/  IWARP_RAMROD_CMD_ID_CREATE_QP ; 
 int IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET ; 
 int /*<<< orphan*/  IWARP_SHARED_QUEUE_PAGE_SIZE ; 
 int IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET ; 
 int /*<<< orphan*/  PQ_FLAGS_ACK ; 
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_get_cm_pq_idx (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_iwarp_alloc_cid (struct qed_hwfn*,scalar_t__*) ; 
 int /*<<< orphan*/  qed_iwarp_cid_cleaned (struct qed_hwfn*,scalar_t__) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

int qed_iwarp_create_qp(struct qed_hwfn *p_hwfn,
			struct qed_rdma_qp *qp,
			struct qed_rdma_create_qp_out_params *out_params)
{
	struct iwarp_create_qp_ramrod_data *p_ramrod;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	u16 physical_queue;
	u32 cid;
	int rc;

	qp->shared_queue = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
					      IWARP_SHARED_QUEUE_PAGE_SIZE,
					      &qp->shared_queue_phys_addr,
					      GFP_KERNEL);
	if (!qp->shared_queue)
		return -ENOMEM;

	out_params->sq_pbl_virt = (u8 *)qp->shared_queue +
	    IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET;
	out_params->sq_pbl_phys = qp->shared_queue_phys_addr +
	    IWARP_SHARED_QUEUE_PAGE_SQ_PBL_OFFSET;
	out_params->rq_pbl_virt = (u8 *)qp->shared_queue +
	    IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET;
	out_params->rq_pbl_phys = qp->shared_queue_phys_addr +
	    IWARP_SHARED_QUEUE_PAGE_RQ_PBL_OFFSET;

	rc = qed_iwarp_alloc_cid(p_hwfn, &cid);
	if (rc)
		goto err1;

	qp->icid = (u16)cid;

	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.cid = qp->icid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_CREATE_QP,
				 PROTOCOLID_IWARP, &init_data);
	if (rc)
		goto err2;

	p_ramrod = &p_ent->ramrod.iwarp_create_qp;

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_FMR_AND_RESERVED_EN,
		  qp->fmr_and_reserved_lkey);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_SIGNALED_COMP, qp->signal_all);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_RDMA_RD_EN,
		  qp->incoming_rdma_read_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_RDMA_WR_EN,
		  qp->incoming_rdma_write_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIELD(p_ramrod->flags,
		  IWARP_CREATE_QP_RAMROD_DATA_SRQ_FLG, qp->use_srq);

	p_ramrod->pd = qp->pd;
	p_ramrod->sq_num_pages = qp->sq_num_pages;
	p_ramrod->rq_num_pages = qp->rq_num_pages;

	p_ramrod->srq_id.srq_idx = cpu_to_le16(qp->srq_id);
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(p_hwfn->hw_info.opaque_fid);
	p_ramrod->qp_handle_for_cqe.hi = cpu_to_le32(qp->qp_handle.hi);
	p_ramrod->qp_handle_for_cqe.lo = cpu_to_le32(qp->qp_handle.lo);

	p_ramrod->cq_cid_for_sq =
	    cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) | qp->sq_cq_id);
	p_ramrod->cq_cid_for_rq =
	    cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) | qp->rq_cq_id);

	p_ramrod->dpi = cpu_to_le16(qp->dpi);

	physical_queue = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_ramrod->physical_q0 = cpu_to_le16(physical_queue);
	physical_queue = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_ACK);
	p_ramrod->physical_q1 = cpu_to_le16(physical_queue);

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc)
		goto err2;

	return rc;

err2:
	qed_iwarp_cid_cleaned(p_hwfn, cid);
err1:
	dma_free_coherent(&p_hwfn->cdev->pdev->dev,
			  IWARP_SHARED_QUEUE_PAGE_SIZE,
			  qp->shared_queue, qp->shared_queue_phys_addr);

	return rc;
}