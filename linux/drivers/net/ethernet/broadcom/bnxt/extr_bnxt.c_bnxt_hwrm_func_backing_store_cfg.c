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
typedef  int u32 ;
struct hwrm_func_backing_store_cfg_input {void* flags; void* tqm_entry_size; int /*<<< orphan*/  tqm_sp_page_dir; int /*<<< orphan*/  tqm_sp_pg_size_tqm_sp_lvl; void* tqm_sp_num_entries; int /*<<< orphan*/  tim_page_dir; int /*<<< orphan*/  tim_pg_size_tim_lvl; void* tim_entry_size; void* tim_num_entries; int /*<<< orphan*/  mrav_page_dir; int /*<<< orphan*/  mrav_pg_size_mrav_lvl; void* mrav_entry_size; void* mrav_num_entries; int /*<<< orphan*/  stat_page_dir; int /*<<< orphan*/  stat_pg_size_stat_lvl; void* stat_entry_size; void* stat_num_entries; int /*<<< orphan*/  vnic_page_dir; int /*<<< orphan*/  vnic_pg_size_vnic_lvl; void* vnic_entry_size; void* vnic_num_ring_table_entries; void* vnic_num_vnic_entries; int /*<<< orphan*/  cq_page_dir; int /*<<< orphan*/  cq_pg_size_cq_lvl; void* cq_entry_size; void* cq_num_l2_entries; void* cq_num_entries; int /*<<< orphan*/  srq_page_dir; int /*<<< orphan*/  srq_pg_size_srq_lvl; void* srq_entry_size; void* srq_num_l2_entries; void* srq_num_entries; int /*<<< orphan*/  qpc_page_dir; int /*<<< orphan*/  qpc_pg_size_qpc_lvl; void* qp_entry_size; void* qp_num_l2_entries; void* qp_num_qp1_entries; void* qp_num_entries; void* enables; int /*<<< orphan*/  member_0; } ;
struct bnxt_ctx_pg_info {int entries; int /*<<< orphan*/  ring_mem; } ;
struct bnxt_ctx_mem_info {int stat_max_entries; struct bnxt_ctx_pg_info** tqm_mem; int /*<<< orphan*/  tqm_entry_size; int /*<<< orphan*/  tim_entry_size; struct bnxt_ctx_pg_info tim_mem; int /*<<< orphan*/  mrav_entry_size; scalar_t__ mrav_num_entries_units; struct bnxt_ctx_pg_info mrav_mem; int /*<<< orphan*/  stat_entry_size; struct bnxt_ctx_pg_info stat_mem; int /*<<< orphan*/  vnic_entry_size; int /*<<< orphan*/  vnic_max_ring_table_entries; int /*<<< orphan*/  vnic_max_vnic_entries; struct bnxt_ctx_pg_info vnic_mem; int /*<<< orphan*/  cq_entry_size; int /*<<< orphan*/  cq_max_l2_entries; struct bnxt_ctx_pg_info cq_mem; int /*<<< orphan*/  srq_entry_size; int /*<<< orphan*/  srq_max_l2_entries; struct bnxt_ctx_pg_info srq_mem; int /*<<< orphan*/  qp_entry_size; int /*<<< orphan*/  qp_max_l2_entries; int /*<<< orphan*/  qp_min_qp1_entries; struct bnxt_ctx_pg_info qp_mem; } ;
struct bnxt {struct bnxt_ctx_mem_info* ctx; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  void* __le32 ;

/* Variables and functions */
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_CQ ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_MRAV ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_QP ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_SRQ ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_STAT ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_TIM ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_SP ; 
 int FUNC_BACKING_STORE_CFG_REQ_ENABLES_VNIC ; 
 int FUNC_BACKING_STORE_CFG_REQ_FLAGS_MRAV_RESERVATION_SPLIT ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_BACKING_STORE_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_backing_store_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_set_pg_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_func_backing_store_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_func_backing_store_cfg(struct bnxt *bp, u32 enables)
{
	struct hwrm_func_backing_store_cfg_input req = {0};
	struct bnxt_ctx_mem_info *ctx = bp->ctx;
	struct bnxt_ctx_pg_info *ctx_pg;
	__le32 *num_entries;
	__le64 *pg_dir;
	u32 flags = 0;
	u8 *pg_attr;
	int i, rc;
	u32 ena;

	if (!ctx)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_BACKING_STORE_CFG, -1, -1);
	req.enables = cpu_to_le32(enables);

	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_QP) {
		ctx_pg = &ctx->qp_mem;
		req.qp_num_entries = cpu_to_le32(ctx_pg->entries);
		req.qp_num_qp1_entries = cpu_to_le16(ctx->qp_min_qp1_entries);
		req.qp_num_l2_entries = cpu_to_le16(ctx->qp_max_l2_entries);
		req.qp_entry_size = cpu_to_le16(ctx->qp_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.qpc_pg_size_qpc_lvl,
				      &req.qpc_page_dir);
	}
	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_SRQ) {
		ctx_pg = &ctx->srq_mem;
		req.srq_num_entries = cpu_to_le32(ctx_pg->entries);
		req.srq_num_l2_entries = cpu_to_le16(ctx->srq_max_l2_entries);
		req.srq_entry_size = cpu_to_le16(ctx->srq_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.srq_pg_size_srq_lvl,
				      &req.srq_page_dir);
	}
	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_CQ) {
		ctx_pg = &ctx->cq_mem;
		req.cq_num_entries = cpu_to_le32(ctx_pg->entries);
		req.cq_num_l2_entries = cpu_to_le16(ctx->cq_max_l2_entries);
		req.cq_entry_size = cpu_to_le16(ctx->cq_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem, &req.cq_pg_size_cq_lvl,
				      &req.cq_page_dir);
	}
	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_VNIC) {
		ctx_pg = &ctx->vnic_mem;
		req.vnic_num_vnic_entries =
			cpu_to_le16(ctx->vnic_max_vnic_entries);
		req.vnic_num_ring_table_entries =
			cpu_to_le16(ctx->vnic_max_ring_table_entries);
		req.vnic_entry_size = cpu_to_le16(ctx->vnic_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.vnic_pg_size_vnic_lvl,
				      &req.vnic_page_dir);
	}
	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_STAT) {
		ctx_pg = &ctx->stat_mem;
		req.stat_num_entries = cpu_to_le32(ctx->stat_max_entries);
		req.stat_entry_size = cpu_to_le16(ctx->stat_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.stat_pg_size_stat_lvl,
				      &req.stat_page_dir);
	}
	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_MRAV) {
		ctx_pg = &ctx->mrav_mem;
		req.mrav_num_entries = cpu_to_le32(ctx_pg->entries);
		if (ctx->mrav_num_entries_units)
			flags |=
			FUNC_BACKING_STORE_CFG_REQ_FLAGS_MRAV_RESERVATION_SPLIT;
		req.mrav_entry_size = cpu_to_le16(ctx->mrav_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.mrav_pg_size_mrav_lvl,
				      &req.mrav_page_dir);
	}
	if (enables & FUNC_BACKING_STORE_CFG_REQ_ENABLES_TIM) {
		ctx_pg = &ctx->tim_mem;
		req.tim_num_entries = cpu_to_le32(ctx_pg->entries);
		req.tim_entry_size = cpu_to_le16(ctx->tim_entry_size);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem,
				      &req.tim_pg_size_tim_lvl,
				      &req.tim_page_dir);
	}
	for (i = 0, num_entries = &req.tqm_sp_num_entries,
	     pg_attr = &req.tqm_sp_pg_size_tqm_sp_lvl,
	     pg_dir = &req.tqm_sp_page_dir,
	     ena = FUNC_BACKING_STORE_CFG_REQ_ENABLES_TQM_SP;
	     i < 9; i++, num_entries++, pg_attr++, pg_dir++, ena <<= 1) {
		if (!(enables & ena))
			continue;

		req.tqm_entry_size = cpu_to_le16(ctx->tqm_entry_size);
		ctx_pg = ctx->tqm_mem[i];
		*num_entries = cpu_to_le32(ctx_pg->entries);
		bnxt_hwrm_set_pg_attr(&ctx_pg->ring_mem, pg_attr, pg_dir);
	}
	req.flags = cpu_to_le32(flags);
	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	return rc;
}