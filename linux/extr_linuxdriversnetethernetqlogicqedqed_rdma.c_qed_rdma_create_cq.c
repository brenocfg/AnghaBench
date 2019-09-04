#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {void* lo; void* hi; } ;
struct rdma_create_cq_ramrod_data {int toggle_bit; int /*<<< orphan*/  int_timeout; scalar_t__ cnq_id; void* pbl_num_pages; int /*<<< orphan*/  pbl_addr; void* max_cqes; int /*<<< orphan*/  is_two_level_pbl; void* dpi; TYPE_3__ cq_handle; } ;
struct TYPE_5__ {struct rdma_create_cq_ramrod_data rdma_create_cq; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; scalar_t__ cid; } ;
struct qed_rdma_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  cq_map; int /*<<< orphan*/  proto; } ;
struct qed_rdma_create_cq_in_params {int /*<<< orphan*/  int_timeout; scalar_t__ cnq_id; int /*<<< orphan*/  pbl_num_pages; int /*<<< orphan*/  pbl_ptr; int /*<<< orphan*/  cq_size; int /*<<< orphan*/  pbl_two_level; int /*<<< orphan*/  dpi; int /*<<< orphan*/  cq_handle_lo; int /*<<< orphan*/  cq_handle_hi; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; struct qed_rdma_info* p_rdma_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum qed_rdma_toggle_bit { ____Placeholder_qed_rdma_toggle_bit } qed_rdma_toggle_bit ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  QED_ELEM_CXT ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_CNQ_RAM ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  RDMA_RAMROD_CREATE_CQ ; 
 scalar_t__ RESC_START (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_bmap_release_id (struct qed_hwfn*,int /*<<< orphan*/ *,scalar_t__) ; 
 int qed_cxt_dynamic_ilt_alloc (struct qed_hwfn*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ qed_cxt_get_proto_cid_start (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_rdma_bmap_alloc_id (struct qed_hwfn*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int qed_rdma_toggle_bit_create_resize_cq (struct qed_hwfn*,scalar_t__) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_rdma_create_cq(void *rdma_cxt,
			      struct qed_rdma_create_cq_in_params *params,
			      u16 *icid)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	struct qed_rdma_info *p_info = p_hwfn->p_rdma_info;
	struct rdma_create_cq_ramrod_data *p_ramrod;
	enum qed_rdma_toggle_bit toggle_bit;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	u32 returned_id, start_cid;
	int rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "cq_handle = %08x%08x\n",
		   params->cq_handle_hi, params->cq_handle_lo);

	/* Allocate icid */
	spin_lock_bh(&p_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_info->cq_map, &returned_id);
	spin_unlock_bh(&p_info->lock);

	if (rc) {
		DP_NOTICE(p_hwfn, "Can't create CQ, rc = %d\n", rc);
		return rc;
	}

	start_cid = qed_cxt_get_proto_cid_start(p_hwfn,
						p_info->proto);
	*icid = returned_id + start_cid;

	/* Check if icid requires a page allocation */
	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_CXT, *icid);
	if (rc)
		goto err;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = *icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	/* Send create CQ ramrod */
	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_CREATE_CQ,
				 p_info->proto, &init_data);
	if (rc)
		goto err;

	p_ramrod = &p_ent->ramrod.rdma_create_cq;

	p_ramrod->cq_handle.hi = cpu_to_le32(params->cq_handle_hi);
	p_ramrod->cq_handle.lo = cpu_to_le32(params->cq_handle_lo);
	p_ramrod->dpi = cpu_to_le16(params->dpi);
	p_ramrod->is_two_level_pbl = params->pbl_two_level;
	p_ramrod->max_cqes = cpu_to_le32(params->cq_size);
	DMA_REGPAIR_LE(p_ramrod->pbl_addr, params->pbl_ptr);
	p_ramrod->pbl_num_pages = cpu_to_le16(params->pbl_num_pages);
	p_ramrod->cnq_id = (u8)RESC_START(p_hwfn, QED_RDMA_CNQ_RAM) +
			   params->cnq_id;
	p_ramrod->int_timeout = params->int_timeout;

	/* toggle the bit for every resize or create cq for a given icid */
	toggle_bit = qed_rdma_toggle_bit_create_resize_cq(p_hwfn, *icid);

	p_ramrod->toggle_bit = toggle_bit;

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc) {
		/* restore toggle bit */
		qed_rdma_toggle_bit_create_resize_cq(p_hwfn, *icid);
		goto err;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Created CQ, rc = %d\n", rc);
	return rc;

err:
	/* release allocated icid */
	spin_lock_bh(&p_info->lock);
	qed_bmap_release_id(p_hwfn, &p_info->cq_map, returned_id);
	spin_unlock_bh(&p_info->lock);
	DP_NOTICE(p_hwfn, "Create CQ failed, rc = %d\n", rc);

	return rc;
}