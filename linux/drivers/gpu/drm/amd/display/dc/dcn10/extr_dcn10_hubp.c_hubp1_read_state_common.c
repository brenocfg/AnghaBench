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
struct hubp {int dummy; } ;
struct _vcs_dpi_display_rq_regs_st {int /*<<< orphan*/  crq_expansion_mode; int /*<<< orphan*/  mrq_expansion_mode; int /*<<< orphan*/  prq_expansion_mode; int /*<<< orphan*/  drq_expansion_mode; int /*<<< orphan*/  plane1_base_address; } ;
struct _vcs_dpi_display_ttu_regs_st {int /*<<< orphan*/  refcyc_per_req_delivery_pre_c; int /*<<< orphan*/  qos_ramp_disable_c; int /*<<< orphan*/  qos_level_fixed_c; int /*<<< orphan*/  refcyc_per_req_delivery_c; int /*<<< orphan*/  refcyc_per_req_delivery_pre_l; int /*<<< orphan*/  qos_ramp_disable_l; int /*<<< orphan*/  qos_level_fixed_l; int /*<<< orphan*/  refcyc_per_req_delivery_l; int /*<<< orphan*/  qos_level_flip; int /*<<< orphan*/  min_ttu_vblank; int /*<<< orphan*/  qos_level_high_wm; int /*<<< orphan*/  qos_level_low_wm; } ;
struct _vcs_dpi_display_dlg_regs_st {int /*<<< orphan*/  refcyc_per_meta_chunk_nom_c; int /*<<< orphan*/  dst_y_per_meta_row_nom_c; int /*<<< orphan*/  refcyc_per_pte_group_nom_c; int /*<<< orphan*/  dst_y_per_pte_row_nom_c; int /*<<< orphan*/  refcyc_per_meta_chunk_vblank_c; int /*<<< orphan*/  refcyc_per_pte_group_vblank_c; int /*<<< orphan*/  vratio_prefetch_c; int /*<<< orphan*/  refcyc_per_line_delivery_c; int /*<<< orphan*/  refcyc_per_line_delivery_l; int /*<<< orphan*/  refcyc_per_line_delivery_pre_c; int /*<<< orphan*/  refcyc_per_line_delivery_pre_l; int /*<<< orphan*/  refcyc_per_meta_chunk_nom_l; int /*<<< orphan*/  dst_y_per_meta_row_nom_l; int /*<<< orphan*/  refcyc_per_pte_group_nom_l; int /*<<< orphan*/  dst_y_per_pte_row_nom_l; int /*<<< orphan*/  refcyc_per_meta_chunk_vblank_l; int /*<<< orphan*/  refcyc_per_pte_group_vblank_l; int /*<<< orphan*/  ref_freq_to_pix_freq; int /*<<< orphan*/  dst_y_per_row_vblank; int /*<<< orphan*/  dst_y_per_vm_vblank; int /*<<< orphan*/  vratio_prefetch; int /*<<< orphan*/  dst_y_prefetch; int /*<<< orphan*/  dst_y_after_scaler; int /*<<< orphan*/  refcyc_x_after_scaler; int /*<<< orphan*/  refcyc_per_htotal; int /*<<< orphan*/  min_dst_y_next_start; int /*<<< orphan*/  dlg_vblank_end; int /*<<< orphan*/  refcyc_h_blank_end; } ;
struct dcn_hubp_state {int /*<<< orphan*/  qos_level_high_wm; int /*<<< orphan*/  qos_level_low_wm; int /*<<< orphan*/  min_ttu_vblank; int /*<<< orphan*/  underflow_status; int /*<<< orphan*/  ttu_disable; int /*<<< orphan*/  blank_en; int /*<<< orphan*/  dcc_en; int /*<<< orphan*/  sw_mode; int /*<<< orphan*/  h_mirror_en; int /*<<< orphan*/  rotation_angle; int /*<<< orphan*/  viewport_height; int /*<<< orphan*/  viewport_width; int /*<<< orphan*/  inuse_addr_lo; int /*<<< orphan*/  inuse_addr_hi; int /*<<< orphan*/  pixel_format; struct _vcs_dpi_display_rq_regs_st rq_regs; struct _vcs_dpi_display_ttu_regs_st ttu_attr; struct _vcs_dpi_display_dlg_regs_st dlg_attr; } ;
struct dcn10_hubp {struct dcn_hubp_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_OFFSET_0 ; 
 int /*<<< orphan*/  BLANK_OFFSET_1 ; 
 int /*<<< orphan*/  CRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  DCHUBP_CNTL ; 
 int /*<<< orphan*/  DCN_EXPANSION_MODE ; 
 int /*<<< orphan*/  DCN_GLOBAL_TTU_CNTL ; 
 int /*<<< orphan*/  DCN_SURF0_TTU_CNTL0 ; 
 int /*<<< orphan*/  DCN_SURF0_TTU_CNTL1 ; 
 int /*<<< orphan*/  DCN_SURF1_TTU_CNTL0 ; 
 int /*<<< orphan*/  DCN_SURF1_TTU_CNTL1 ; 
 int /*<<< orphan*/  DCN_TTU_QOS_WM ; 
 int /*<<< orphan*/  DCSURF_PRI_VIEWPORT_DIMENSION ; 
 int /*<<< orphan*/  DCSURF_SURFACE_CONFIG ; 
 int /*<<< orphan*/  DCSURF_SURFACE_CONTROL ; 
 int /*<<< orphan*/  DCSURF_SURFACE_EARLIEST_INUSE ; 
 int /*<<< orphan*/  DCSURF_SURFACE_EARLIEST_INUSE_HIGH ; 
 int /*<<< orphan*/  DCSURF_TILING_CONFIG ; 
 int /*<<< orphan*/  DET_BUF_PLANE1_BASE_ADDRESS ; 
 int /*<<< orphan*/  DLG_V_BLANK_END ; 
 int /*<<< orphan*/  DRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  DST_AFTER_SCALER ; 
 int /*<<< orphan*/  DST_DIMENSIONS ; 
 int /*<<< orphan*/  DST_Y_AFTER_SCALER ; 
 int /*<<< orphan*/  DST_Y_PER_META_ROW_NOM_C ; 
 int /*<<< orphan*/  DST_Y_PER_META_ROW_NOM_L ; 
 int /*<<< orphan*/  DST_Y_PER_PTE_ROW_NOM_C ; 
 int /*<<< orphan*/  DST_Y_PER_PTE_ROW_NOM_L ; 
 int /*<<< orphan*/  DST_Y_PER_ROW_VBLANK ; 
 int /*<<< orphan*/  DST_Y_PER_VM_VBLANK ; 
 int /*<<< orphan*/  DST_Y_PREFETCH ; 
 int /*<<< orphan*/  HUBPRET_CONTROL ; 
 int /*<<< orphan*/  HUBP_BLANK_EN ; 
 int /*<<< orphan*/  HUBP_TTU_DISABLE ; 
 int /*<<< orphan*/  HUBP_UNDERFLOW_STATUS ; 
 int /*<<< orphan*/  H_MIRROR_EN ; 
 int /*<<< orphan*/  MIN_DST_Y_NEXT_START ; 
 int /*<<< orphan*/  MIN_TTU_VBLANK ; 
 int /*<<< orphan*/  MRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  NOM_PARAMETERS_0 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_1 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_2 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_3 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_4 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_5 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_6 ; 
 int /*<<< orphan*/  NOM_PARAMETERS_7 ; 
 int /*<<< orphan*/  PER_LINE_DELIVERY ; 
 int /*<<< orphan*/  PER_LINE_DELIVERY_PRE ; 
 int /*<<< orphan*/  PREFETCH_SETTINGS ; 
 int /*<<< orphan*/  PREFETCH_SETTINGS_C ; 
 int /*<<< orphan*/  PREFETCH_SETTINS ; 
 int /*<<< orphan*/  PREFETCH_SETTINS_C ; 
 int /*<<< orphan*/  PRIMARY_SURFACE_DCC_EN ; 
 int /*<<< orphan*/  PRI_VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  PRI_VIEWPORT_WIDTH ; 
 int /*<<< orphan*/  PRQ_EXPANSION_MODE ; 
 int /*<<< orphan*/  QoS_LEVEL_FIXED ; 
 int /*<<< orphan*/  QoS_LEVEL_FLIP ; 
 int /*<<< orphan*/  QoS_LEVEL_HIGH_WM ; 
 int /*<<< orphan*/  QoS_LEVEL_LOW_WM ; 
 int /*<<< orphan*/  QoS_RAMP_DISABLE ; 
 int /*<<< orphan*/  REFCYC_H_BLANK_END ; 
 int /*<<< orphan*/  REFCYC_PER_HTOTAL ; 
 int /*<<< orphan*/  REFCYC_PER_LINE_DELIVERY_C ; 
 int /*<<< orphan*/  REFCYC_PER_LINE_DELIVERY_L ; 
 int /*<<< orphan*/  REFCYC_PER_LINE_DELIVERY_PRE_C ; 
 int /*<<< orphan*/  REFCYC_PER_LINE_DELIVERY_PRE_L ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_NOM_C ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_NOM_L ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_VBLANK_C ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_VBLANK_L ; 
 int /*<<< orphan*/  REFCYC_PER_PTE_GROUP_NOM_C ; 
 int /*<<< orphan*/  REFCYC_PER_PTE_GROUP_NOM_L ; 
 int /*<<< orphan*/  REFCYC_PER_PTE_GROUP_VBLANK_C ; 
 int /*<<< orphan*/  REFCYC_PER_PTE_GROUP_VBLANK_L ; 
 int /*<<< orphan*/  REFCYC_PER_REQ_DELIVERY ; 
 int /*<<< orphan*/  REFCYC_PER_REQ_DELIVERY_PRE ; 
 int /*<<< orphan*/  REFCYC_X_AFTER_SCALER ; 
 int /*<<< orphan*/  REF_FREQ_TO_PIX_FREQ ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_GET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_GET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ROTATION_ANGLE ; 
 int /*<<< orphan*/  SURFACE_EARLIEST_INUSE_ADDRESS ; 
 int /*<<< orphan*/  SURFACE_EARLIEST_INUSE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT ; 
 int /*<<< orphan*/  SW_MODE ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_0 ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_1 ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_2 ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_3 ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_4 ; 
 int /*<<< orphan*/  VRATIO_PREFETCH ; 
 int /*<<< orphan*/  VRATIO_PREFETCH_C ; 

void hubp1_read_state_common(struct hubp *hubp)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	struct dcn_hubp_state *s = &hubp1->state;
	struct _vcs_dpi_display_dlg_regs_st *dlg_attr = &s->dlg_attr;
	struct _vcs_dpi_display_ttu_regs_st *ttu_attr = &s->ttu_attr;
	struct _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

	/* Requester */
	REG_GET(HUBPRET_CONTROL,
			DET_BUF_PLANE1_BASE_ADDRESS, &rq_regs->plane1_base_address);
	REG_GET_4(DCN_EXPANSION_MODE,
			DRQ_EXPANSION_MODE, &rq_regs->drq_expansion_mode,
			PRQ_EXPANSION_MODE, &rq_regs->prq_expansion_mode,
			MRQ_EXPANSION_MODE, &rq_regs->mrq_expansion_mode,
			CRQ_EXPANSION_MODE, &rq_regs->crq_expansion_mode);

	/* DLG - Per hubp */
	REG_GET_2(BLANK_OFFSET_0,
		REFCYC_H_BLANK_END, &dlg_attr->refcyc_h_blank_end,
		DLG_V_BLANK_END, &dlg_attr->dlg_vblank_end);

	REG_GET(BLANK_OFFSET_1,
		MIN_DST_Y_NEXT_START, &dlg_attr->min_dst_y_next_start);

	REG_GET(DST_DIMENSIONS,
		REFCYC_PER_HTOTAL, &dlg_attr->refcyc_per_htotal);

	REG_GET_2(DST_AFTER_SCALER,
		REFCYC_X_AFTER_SCALER, &dlg_attr->refcyc_x_after_scaler,
		DST_Y_AFTER_SCALER, &dlg_attr->dst_y_after_scaler);

	if (REG(PREFETCH_SETTINS))
		REG_GET_2(PREFETCH_SETTINS,
			DST_Y_PREFETCH, &dlg_attr->dst_y_prefetch,
			VRATIO_PREFETCH, &dlg_attr->vratio_prefetch);
	else
		REG_GET_2(PREFETCH_SETTINGS,
			DST_Y_PREFETCH, &dlg_attr->dst_y_prefetch,
			VRATIO_PREFETCH, &dlg_attr->vratio_prefetch);

	REG_GET_2(VBLANK_PARAMETERS_0,
		DST_Y_PER_VM_VBLANK, &dlg_attr->dst_y_per_vm_vblank,
		DST_Y_PER_ROW_VBLANK, &dlg_attr->dst_y_per_row_vblank);

	REG_GET(REF_FREQ_TO_PIX_FREQ,
		REF_FREQ_TO_PIX_FREQ, &dlg_attr->ref_freq_to_pix_freq);

	/* DLG - Per luma/chroma */
	REG_GET(VBLANK_PARAMETERS_1,
		REFCYC_PER_PTE_GROUP_VBLANK_L, &dlg_attr->refcyc_per_pte_group_vblank_l);

	REG_GET(VBLANK_PARAMETERS_3,
		REFCYC_PER_META_CHUNK_VBLANK_L, &dlg_attr->refcyc_per_meta_chunk_vblank_l);

	if (REG(NOM_PARAMETERS_0))
		REG_GET(NOM_PARAMETERS_0,
			DST_Y_PER_PTE_ROW_NOM_L, &dlg_attr->dst_y_per_pte_row_nom_l);

	if (REG(NOM_PARAMETERS_1))
		REG_GET(NOM_PARAMETERS_1,
			REFCYC_PER_PTE_GROUP_NOM_L, &dlg_attr->refcyc_per_pte_group_nom_l);

	REG_GET(NOM_PARAMETERS_4,
		DST_Y_PER_META_ROW_NOM_L, &dlg_attr->dst_y_per_meta_row_nom_l);

	REG_GET(NOM_PARAMETERS_5,
		REFCYC_PER_META_CHUNK_NOM_L, &dlg_attr->refcyc_per_meta_chunk_nom_l);

	REG_GET_2(PER_LINE_DELIVERY_PRE,
		REFCYC_PER_LINE_DELIVERY_PRE_L, &dlg_attr->refcyc_per_line_delivery_pre_l,
		REFCYC_PER_LINE_DELIVERY_PRE_C, &dlg_attr->refcyc_per_line_delivery_pre_c);

	REG_GET_2(PER_LINE_DELIVERY,
		REFCYC_PER_LINE_DELIVERY_L, &dlg_attr->refcyc_per_line_delivery_l,
		REFCYC_PER_LINE_DELIVERY_C, &dlg_attr->refcyc_per_line_delivery_c);

	if (REG(PREFETCH_SETTINS_C))
		REG_GET(PREFETCH_SETTINS_C,
			VRATIO_PREFETCH_C, &dlg_attr->vratio_prefetch_c);
	else
		REG_GET(PREFETCH_SETTINGS_C,
			VRATIO_PREFETCH_C, &dlg_attr->vratio_prefetch_c);

	REG_GET(VBLANK_PARAMETERS_2,
		REFCYC_PER_PTE_GROUP_VBLANK_C, &dlg_attr->refcyc_per_pte_group_vblank_c);

	REG_GET(VBLANK_PARAMETERS_4,
		REFCYC_PER_META_CHUNK_VBLANK_C, &dlg_attr->refcyc_per_meta_chunk_vblank_c);

	if (REG(NOM_PARAMETERS_2))
		REG_GET(NOM_PARAMETERS_2,
			DST_Y_PER_PTE_ROW_NOM_C, &dlg_attr->dst_y_per_pte_row_nom_c);

	if (REG(NOM_PARAMETERS_3))
		REG_GET(NOM_PARAMETERS_3,
			REFCYC_PER_PTE_GROUP_NOM_C, &dlg_attr->refcyc_per_pte_group_nom_c);

	REG_GET(NOM_PARAMETERS_6,
		DST_Y_PER_META_ROW_NOM_C, &dlg_attr->dst_y_per_meta_row_nom_c);

	REG_GET(NOM_PARAMETERS_7,
		REFCYC_PER_META_CHUNK_NOM_C, &dlg_attr->refcyc_per_meta_chunk_nom_c);

	/* TTU - per hubp */
	REG_GET_2(DCN_TTU_QOS_WM,
		QoS_LEVEL_LOW_WM, &ttu_attr->qos_level_low_wm,
		QoS_LEVEL_HIGH_WM, &ttu_attr->qos_level_high_wm);

	REG_GET_2(DCN_GLOBAL_TTU_CNTL,
		MIN_TTU_VBLANK, &ttu_attr->min_ttu_vblank,
		QoS_LEVEL_FLIP, &ttu_attr->qos_level_flip);

	/* TTU - per luma/chroma */
	/* Assumed surf0 is luma and 1 is chroma */

	REG_GET_3(DCN_SURF0_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr->refcyc_per_req_delivery_l,
		QoS_LEVEL_FIXED, &ttu_attr->qos_level_fixed_l,
		QoS_RAMP_DISABLE, &ttu_attr->qos_ramp_disable_l);

	REG_GET(DCN_SURF0_TTU_CNTL1,
		REFCYC_PER_REQ_DELIVERY_PRE,
		&ttu_attr->refcyc_per_req_delivery_pre_l);

	REG_GET_3(DCN_SURF1_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr->refcyc_per_req_delivery_c,
		QoS_LEVEL_FIXED, &ttu_attr->qos_level_fixed_c,
		QoS_RAMP_DISABLE, &ttu_attr->qos_ramp_disable_c);

	REG_GET(DCN_SURF1_TTU_CNTL1,
		REFCYC_PER_REQ_DELIVERY_PRE,
		&ttu_attr->refcyc_per_req_delivery_pre_c);

	/* Rest of hubp */
	REG_GET(DCSURF_SURFACE_CONFIG,
			SURFACE_PIXEL_FORMAT, &s->pixel_format);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE_HIGH,
			SURFACE_EARLIEST_INUSE_ADDRESS_HIGH, &s->inuse_addr_hi);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE,
			SURFACE_EARLIEST_INUSE_ADDRESS, &s->inuse_addr_lo);

	REG_GET_2(DCSURF_PRI_VIEWPORT_DIMENSION,
			PRI_VIEWPORT_WIDTH, &s->viewport_width,
			PRI_VIEWPORT_HEIGHT, &s->viewport_height);

	REG_GET_2(DCSURF_SURFACE_CONFIG,
			ROTATION_ANGLE, &s->rotation_angle,
			H_MIRROR_EN, &s->h_mirror_en);

	REG_GET(DCSURF_TILING_CONFIG,
			SW_MODE, &s->sw_mode);

	REG_GET(DCSURF_SURFACE_CONTROL,
			PRIMARY_SURFACE_DCC_EN, &s->dcc_en);

	REG_GET_3(DCHUBP_CNTL,
			HUBP_BLANK_EN, &s->blank_en,
			HUBP_TTU_DISABLE, &s->ttu_disable,
			HUBP_UNDERFLOW_STATUS, &s->underflow_status);

	REG_GET(DCN_GLOBAL_TTU_CNTL,
			MIN_TTU_VBLANK, &s->min_ttu_vblank);

	REG_GET_2(DCN_TTU_QOS_WM,
			QoS_LEVEL_LOW_WM, &s->qos_level_low_wm,
			QoS_LEVEL_HIGH_WM, &s->qos_level_high_wm);

}