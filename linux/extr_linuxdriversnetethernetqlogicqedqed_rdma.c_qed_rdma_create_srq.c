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
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct TYPE_7__ {void* opaque_fid; void* srq_idx; } ;
struct rdma_srq_create_ramrod_data {int /*<<< orphan*/  producers_addr; void* page_size; TYPE_3__ srq_id; void* pd_id; void* pages_in_srq_pbl; int /*<<< orphan*/  pbl_base_addr; } ;
struct TYPE_6__ {struct rdma_srq_create_ramrod_data rdma_create_srq; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; void* opaque_fid; } ;
struct qed_rdma_create_srq_out_params {void* srq_id; } ;
struct qed_rdma_create_srq_in_params {void* num_pages; void* pd_id; void* page_size; int /*<<< orphan*/  prod_pair_addr; int /*<<< orphan*/  pbl_base_addr; } ;
struct TYPE_5__ {void* opaque_fid; } ;
struct qed_hwfn {TYPE_4__* p_rdma_info; TYPE_1__ hw_info; } ;
struct qed_bmap {int dummy; } ;
typedef  enum qed_cxt_elem_type { ____Placeholder_qed_cxt_elem_type } qed_cxt_elem_type ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  proto; struct qed_bmap srq_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,void*) ; 
 int QED_ELEM_SRQ ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  RDMA_RAMROD_CREATE_SRQ ; 
 void* cpu_to_le16 (void*) ; 
 int /*<<< orphan*/  qed_bmap_release_id (struct qed_hwfn*,struct qed_bmap*,scalar_t__) ; 
 int qed_cxt_dynamic_ilt_alloc (struct qed_hwfn*,int,scalar_t__) ; 
 int qed_rdma_bmap_alloc_id (struct qed_hwfn*,struct qed_bmap*,scalar_t__*) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_rdma_create_srq(void *rdma_cxt,
		    struct qed_rdma_create_srq_in_params *in_params,
		    struct qed_rdma_create_srq_out_params *out_params)
{
	struct rdma_srq_create_ramrod_data *p_ramrod;
	struct qed_sp_init_data init_data = {};
	struct qed_hwfn *p_hwfn = rdma_cxt;
	enum qed_cxt_elem_type elem_type;
	struct qed_spq_entry *p_ent;
	u16 opaque_fid, srq_id;
	struct qed_bmap *bmap;
	u32 returned_id;
	int rc;

	bmap = &p_hwfn->p_rdma_info->srq_map;
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, bmap, &returned_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	if (rc) {
		DP_NOTICE(p_hwfn, "failed to allocate srq id\n");
		return rc;
	}

	elem_type = QED_ELEM_SRQ;
	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, elem_type, returned_id);
	if (rc)
		goto err;
	/* returned id is no greater than u16 */
	srq_id = (u16)returned_id;
	opaque_fid = p_hwfn->hw_info.opaque_fid;

	opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_CREATE_SRQ,
				 p_hwfn->p_rdma_info->proto, &init_data);
	if (rc)
		goto err;

	p_ramrod = &p_ent->ramrod.rdma_create_srq;
	DMA_REGPAIR_LE(p_ramrod->pbl_base_addr, in_params->pbl_base_addr);
	p_ramrod->pages_in_srq_pbl = cpu_to_le16(in_params->num_pages);
	p_ramrod->pd_id = cpu_to_le16(in_params->pd_id);
	p_ramrod->srq_id.srq_idx = cpu_to_le16(srq_id);
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(opaque_fid);
	p_ramrod->page_size = cpu_to_le16(in_params->page_size);
	DMA_REGPAIR_LE(p_ramrod->producers_addr, in_params->prod_pair_addr);

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc)
		goto err;

	out_params->srq_id = srq_id;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "SRQ created Id = %x\n", out_params->srq_id);

	return rc;

err:
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, bmap, returned_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	return rc;
}