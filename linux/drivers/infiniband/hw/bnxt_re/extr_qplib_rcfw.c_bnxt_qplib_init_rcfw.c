#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t u16 ;
struct creq_initialize_fw_resp {int dummy; } ;
struct cmdq_initialize_fw {size_t qpc_pg_size_qpc_lvl; size_t mrw_pg_size_mrw_lvl; size_t srq_pg_size_srq_lvl; size_t cq_pg_size_cq_lvl; size_t tim_pg_size_tim_lvl; size_t tqm_pg_size_tqm_lvl; void* stat_ctx_id; void* max_gid_per_vf; void* max_cq_per_vf; void* max_srq_per_vf; void* max_mrw_per_vf; void* max_qp_per_vf; void* number_of_cq; void* number_of_srq; void* number_of_mrw; void* number_of_qp; void* tqm_page_dir; void* tim_page_dir; void* cq_page_dir; void* srq_page_dir; void* mrw_page_dir; void* qpc_page_dir; int /*<<< orphan*/  log2_dbr_pg_size; } ;
struct bnxt_qplib_rcfw {int /*<<< orphan*/  flags; TYPE_1__* res; } ;
struct TYPE_20__ {int /*<<< orphan*/  fw_id; } ;
struct TYPE_19__ {int /*<<< orphan*/  max_gid_per_vf; int /*<<< orphan*/  max_cq_per_vf; int /*<<< orphan*/  max_srq_per_vf; int /*<<< orphan*/  max_mrw_per_vf; int /*<<< orphan*/  max_qp_per_vf; } ;
struct TYPE_18__ {size_t level; int /*<<< orphan*/  max_elements; TYPE_10__* pbl; } ;
struct TYPE_17__ {size_t level; int /*<<< orphan*/  max_elements; TYPE_10__* pbl; } ;
struct TYPE_16__ {size_t level; int /*<<< orphan*/  max_elements; TYPE_10__* pbl; } ;
struct TYPE_15__ {size_t level; int /*<<< orphan*/  max_elements; TYPE_10__* pbl; } ;
struct TYPE_14__ {TYPE_10__* pbl; } ;
struct TYPE_13__ {size_t level; TYPE_10__* pbl; } ;
struct bnxt_qplib_ctx {size_t tqm_pde_level; TYPE_9__ stats; TYPE_8__ vf_res; TYPE_7__ cq_tbl; TYPE_6__ srqc_tbl; TYPE_5__ mrw_tbl; TYPE_4__ qpc_tbl; TYPE_3__ tqm_pde; TYPE_2__ tim_tbl; } ;
struct TYPE_12__ {int /*<<< orphan*/  cctx; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pg_map_arr; } ;

/* Variables and functions */
 size_t CMDQ_INITIALIZE_FW_CQ_LVL_SFT ; 
 size_t CMDQ_INITIALIZE_FW_MRW_LVL_SFT ; 
 size_t CMDQ_INITIALIZE_FW_QPC_LVL_SFT ; 
 size_t CMDQ_INITIALIZE_FW_SRQ_LVL_SFT ; 
 size_t CMDQ_INITIALIZE_FW_TIM_LVL_SFT ; 
 size_t CMDQ_INITIALIZE_FW_TQM_LVL_SFT ; 
 int /*<<< orphan*/  FIRMWARE_INITIALIZED_FLAG ; 
 int /*<<< orphan*/  INITIALIZE_FW ; 
 scalar_t__ PAGE_SHIFT ; 
 size_t PBL_LVL_0 ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_initialize_fw,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ RCFW_DBR_BASE_PAGE_SHIFT ; 
 size_t __get_pbl_pg_idx (TYPE_10__*) ; 
 scalar_t__ bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ ) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnxt_qplib_init_rcfw(struct bnxt_qplib_rcfw *rcfw,
			 struct bnxt_qplib_ctx *ctx, int is_virtfn)
{
	struct cmdq_initialize_fw req;
	struct creq_initialize_fw_resp resp;
	u16 cmd_flags = 0, level;
	int rc;

	RCFW_CMD_PREP(req, INITIALIZE_FW, cmd_flags);
	/* Supply (log-base-2-of-host-page-size - base-page-shift)
	 * to bono to adjust the doorbell page sizes.
	 */
	req.log2_dbr_pg_size = cpu_to_le16(PAGE_SHIFT -
					   RCFW_DBR_BASE_PAGE_SHIFT);
	/*
	 * Gen P5 devices doesn't require this allocation
	 * as the L2 driver does the same for RoCE also.
	 * Also, VFs need not setup the HW context area, PF
	 * shall setup this area for VF. Skipping the
	 * HW programming
	 */
	if (is_virtfn || bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx))
		goto skip_ctx_setup;

	level = ctx->qpc_tbl.level;
	req.qpc_pg_size_qpc_lvl = (level << CMDQ_INITIALIZE_FW_QPC_LVL_SFT) |
				__get_pbl_pg_idx(&ctx->qpc_tbl.pbl[level]);
	level = ctx->mrw_tbl.level;
	req.mrw_pg_size_mrw_lvl = (level << CMDQ_INITIALIZE_FW_MRW_LVL_SFT) |
				__get_pbl_pg_idx(&ctx->mrw_tbl.pbl[level]);
	level = ctx->srqc_tbl.level;
	req.srq_pg_size_srq_lvl = (level << CMDQ_INITIALIZE_FW_SRQ_LVL_SFT) |
				__get_pbl_pg_idx(&ctx->srqc_tbl.pbl[level]);
	level = ctx->cq_tbl.level;
	req.cq_pg_size_cq_lvl = (level << CMDQ_INITIALIZE_FW_CQ_LVL_SFT) |
				__get_pbl_pg_idx(&ctx->cq_tbl.pbl[level]);
	level = ctx->srqc_tbl.level;
	req.srq_pg_size_srq_lvl = (level << CMDQ_INITIALIZE_FW_SRQ_LVL_SFT) |
				__get_pbl_pg_idx(&ctx->srqc_tbl.pbl[level]);
	level = ctx->cq_tbl.level;
	req.cq_pg_size_cq_lvl = (level << CMDQ_INITIALIZE_FW_CQ_LVL_SFT) |
				__get_pbl_pg_idx(&ctx->cq_tbl.pbl[level]);
	level = ctx->tim_tbl.level;
	req.tim_pg_size_tim_lvl = (level << CMDQ_INITIALIZE_FW_TIM_LVL_SFT) |
				  __get_pbl_pg_idx(&ctx->tim_tbl.pbl[level]);
	level = ctx->tqm_pde_level;
	req.tqm_pg_size_tqm_lvl = (level << CMDQ_INITIALIZE_FW_TQM_LVL_SFT) |
				  __get_pbl_pg_idx(&ctx->tqm_pde.pbl[level]);

	req.qpc_page_dir =
		cpu_to_le64(ctx->qpc_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.mrw_page_dir =
		cpu_to_le64(ctx->mrw_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.srq_page_dir =
		cpu_to_le64(ctx->srqc_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.cq_page_dir =
		cpu_to_le64(ctx->cq_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.tim_page_dir =
		cpu_to_le64(ctx->tim_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.tqm_page_dir =
		cpu_to_le64(ctx->tqm_pde.pbl[PBL_LVL_0].pg_map_arr[0]);

	req.number_of_qp = cpu_to_le32(ctx->qpc_tbl.max_elements);
	req.number_of_mrw = cpu_to_le32(ctx->mrw_tbl.max_elements);
	req.number_of_srq = cpu_to_le32(ctx->srqc_tbl.max_elements);
	req.number_of_cq = cpu_to_le32(ctx->cq_tbl.max_elements);

	req.max_qp_per_vf = cpu_to_le32(ctx->vf_res.max_qp_per_vf);
	req.max_mrw_per_vf = cpu_to_le32(ctx->vf_res.max_mrw_per_vf);
	req.max_srq_per_vf = cpu_to_le32(ctx->vf_res.max_srq_per_vf);
	req.max_cq_per_vf = cpu_to_le32(ctx->vf_res.max_cq_per_vf);
	req.max_gid_per_vf = cpu_to_le32(ctx->vf_res.max_gid_per_vf);

skip_ctx_setup:
	req.stat_ctx_id = cpu_to_le32(ctx->stats.fw_id);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp,
					  NULL, 0);
	if (rc)
		return rc;
	set_bit(FIRMWARE_INITIALIZED_FLAG, &rcfw->flags);
	return 0;
}