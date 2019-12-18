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
struct dcn20_hubp {int dummy; } ;
struct _vcs_dpi_display_ttu_regs_st {int /*<<< orphan*/  qos_level_flip; int /*<<< orphan*/  min_ttu_vblank; int /*<<< orphan*/  refcyc_per_req_delivery_pre_cur1; int /*<<< orphan*/  refcyc_per_req_delivery_pre_cur0; int /*<<< orphan*/  refcyc_per_req_delivery_pre_c; int /*<<< orphan*/  refcyc_per_req_delivery_pre_l; } ;
struct _vcs_dpi_display_dlg_regs_st {int /*<<< orphan*/  refcyc_per_line_delivery_pre_c; int /*<<< orphan*/  refcyc_per_line_delivery_pre_l; int /*<<< orphan*/  refcyc_per_meta_chunk_flip_l; int /*<<< orphan*/  refcyc_per_meta_chunk_vblank_c; int /*<<< orphan*/  refcyc_per_meta_chunk_vblank_l; int /*<<< orphan*/  dst_y_per_row_flip; int /*<<< orphan*/  dst_y_per_vm_flip; int /*<<< orphan*/  dst_y_per_row_vblank; int /*<<< orphan*/  dst_y_per_vm_vblank; int /*<<< orphan*/  vratio_prefetch_c; int /*<<< orphan*/  vratio_prefetch; int /*<<< orphan*/  dst_y_prefetch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCN_CUR0_TTU_CNTL1 ; 
 int /*<<< orphan*/  DCN_CUR1_TTU_CNTL1 ; 
 int /*<<< orphan*/  DCN_GLOBAL_TTU_CNTL ; 
 int /*<<< orphan*/  DCN_SURF0_TTU_CNTL1 ; 
 int /*<<< orphan*/  DCN_SURF1_TTU_CNTL1 ; 
 int /*<<< orphan*/  DST_Y_PER_ROW_FLIP ; 
 int /*<<< orphan*/  DST_Y_PER_ROW_VBLANK ; 
 int /*<<< orphan*/  DST_Y_PER_VM_FLIP ; 
 int /*<<< orphan*/  DST_Y_PER_VM_VBLANK ; 
 int /*<<< orphan*/  DST_Y_PREFETCH ; 
 int /*<<< orphan*/  FLIP_PARAMETERS_0 ; 
 int /*<<< orphan*/  FLIP_PARAMETERS_2 ; 
 int /*<<< orphan*/  MIN_TTU_VBLANK ; 
 int /*<<< orphan*/  PER_LINE_DELIVERY_PRE ; 
 int /*<<< orphan*/  PREFETCH_SETTINGS ; 
 int /*<<< orphan*/  PREFETCH_SETTINGS_C ; 
 int /*<<< orphan*/  QoS_LEVEL_FLIP ; 
 int /*<<< orphan*/  REFCYC_PER_LINE_DELIVERY_PRE_C ; 
 int /*<<< orphan*/  REFCYC_PER_LINE_DELIVERY_PRE_L ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_FLIP_L ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_VBLANK_C ; 
 int /*<<< orphan*/  REFCYC_PER_META_CHUNK_VBLANK_L ; 
 int /*<<< orphan*/  REFCYC_PER_REQ_DELIVERY_PRE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_0 ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_3 ; 
 int /*<<< orphan*/  VBLANK_PARAMETERS_4 ; 
 int /*<<< orphan*/  VRATIO_PREFETCH ; 
 int /*<<< orphan*/  VRATIO_PREFETCH_C ; 

void hubp2_setup_interdependent(
		struct hubp *hubp,
		struct _vcs_dpi_display_dlg_regs_st *dlg_attr,
		struct _vcs_dpi_display_ttu_regs_st *ttu_attr)
{
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_SET_2(PREFETCH_SETTINGS, 0,
			DST_Y_PREFETCH, dlg_attr->dst_y_prefetch,
			VRATIO_PREFETCH, dlg_attr->vratio_prefetch);

	REG_SET(PREFETCH_SETTINGS_C, 0,
			VRATIO_PREFETCH_C, dlg_attr->vratio_prefetch_c);

	REG_SET_2(VBLANK_PARAMETERS_0, 0,
		DST_Y_PER_VM_VBLANK, dlg_attr->dst_y_per_vm_vblank,
		DST_Y_PER_ROW_VBLANK, dlg_attr->dst_y_per_row_vblank);

	REG_SET_2(FLIP_PARAMETERS_0, 0,
		DST_Y_PER_VM_FLIP, dlg_attr->dst_y_per_vm_flip,
		DST_Y_PER_ROW_FLIP, dlg_attr->dst_y_per_row_flip);

	REG_SET(VBLANK_PARAMETERS_3, 0,
		REFCYC_PER_META_CHUNK_VBLANK_L, dlg_attr->refcyc_per_meta_chunk_vblank_l);

	REG_SET(VBLANK_PARAMETERS_4, 0,
		REFCYC_PER_META_CHUNK_VBLANK_C, dlg_attr->refcyc_per_meta_chunk_vblank_c);

	REG_SET(FLIP_PARAMETERS_2, 0,
		REFCYC_PER_META_CHUNK_FLIP_L, dlg_attr->refcyc_per_meta_chunk_flip_l);

	REG_SET_2(PER_LINE_DELIVERY_PRE, 0,
		REFCYC_PER_LINE_DELIVERY_PRE_L, dlg_attr->refcyc_per_line_delivery_pre_l,
		REFCYC_PER_LINE_DELIVERY_PRE_C, dlg_attr->refcyc_per_line_delivery_pre_c);

	REG_SET(DCN_SURF0_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE,
		ttu_attr->refcyc_per_req_delivery_pre_l);
	REG_SET(DCN_SURF1_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE,
		ttu_attr->refcyc_per_req_delivery_pre_c);
	REG_SET(DCN_CUR0_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE, ttu_attr->refcyc_per_req_delivery_pre_cur0);
	REG_SET(DCN_CUR1_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE, ttu_attr->refcyc_per_req_delivery_pre_cur1);

	REG_SET_2(DCN_GLOBAL_TTU_CNTL, 0,
		MIN_TTU_VBLANK, ttu_attr->min_ttu_vblank,
		QoS_LEVEL_FLIP, ttu_attr->qos_level_flip);
}