#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcyc_per_vm_dmdata; int /*<<< orphan*/  xfc_reg_remote_surface_flip_latency; int /*<<< orphan*/  xfc_reg_precharge_delay; int /*<<< orphan*/  xfc_reg_transfer_delay; int /*<<< orphan*/  dst_y_delta_drq_limit; int /*<<< orphan*/  vready_after_vcount0; int /*<<< orphan*/  chunk_hdl_adjust_cur1; int /*<<< orphan*/  dst_y_offset_cur1; int /*<<< orphan*/  chunk_hdl_adjust_cur0; int /*<<< orphan*/  refcyc_per_line_delivery_c; int /*<<< orphan*/  refcyc_per_line_delivery_l; int /*<<< orphan*/  refcyc_per_line_delivery_pre_c; int /*<<< orphan*/  refcyc_per_line_delivery_pre_l; int /*<<< orphan*/  refcyc_per_meta_chunk_nom_c; int /*<<< orphan*/  refcyc_per_meta_chunk_nom_l; int /*<<< orphan*/  dst_y_per_meta_row_nom_c; int /*<<< orphan*/  dst_y_per_meta_row_nom_l; int /*<<< orphan*/  refcyc_per_pte_group_nom_c; int /*<<< orphan*/  refcyc_per_pte_group_nom_l; int /*<<< orphan*/  dst_y_per_pte_row_nom_c; int /*<<< orphan*/  dst_y_per_pte_row_nom_l; int /*<<< orphan*/  refcyc_per_meta_chunk_flip_c; int /*<<< orphan*/  refcyc_per_meta_chunk_flip_l; int /*<<< orphan*/  refcyc_per_pte_group_flip_c; int /*<<< orphan*/  refcyc_per_pte_group_flip_l; int /*<<< orphan*/  refcyc_per_meta_chunk_vblank_c; int /*<<< orphan*/  refcyc_per_meta_chunk_vblank_l; int /*<<< orphan*/  refcyc_per_pte_group_vblank_c; int /*<<< orphan*/  refcyc_per_pte_group_vblank_l; int /*<<< orphan*/  vratio_prefetch_c; int /*<<< orphan*/  vratio_prefetch; int /*<<< orphan*/  ref_freq_to_pix_freq; int /*<<< orphan*/  dst_y_per_row_flip; int /*<<< orphan*/  dst_y_per_vm_flip; int /*<<< orphan*/  dst_y_per_row_vblank; int /*<<< orphan*/  dst_y_per_vm_vblank; int /*<<< orphan*/  dst_y_prefetch; int /*<<< orphan*/  dst_y_after_scaler; int /*<<< orphan*/  refcyc_x_after_scaler; int /*<<< orphan*/  refcyc_per_htotal; int /*<<< orphan*/  min_dst_y_next_start; int /*<<< orphan*/  dlg_vblank_end; int /*<<< orphan*/  refcyc_h_blank_end; } ;
typedef  TYPE_1__ display_dlg_regs_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*,...) ; 

void print__dlg_regs_st(struct display_mode_lib *mode_lib, display_dlg_regs_st dlg_regs)
{
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_DLG_REGS_ST\n");
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_h_blank_end              = 0x%0x\n",
			dlg_regs.refcyc_h_blank_end);
	dml_print(
			"DML_RQ_DLG_CALC:    dlg_vblank_end                  = 0x%0x\n",
			dlg_regs.dlg_vblank_end);
	dml_print(
			"DML_RQ_DLG_CALC:    min_dst_y_next_start            = 0x%0x\n",
			dlg_regs.min_dst_y_next_start);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_htotal               = 0x%0x\n",
			dlg_regs.refcyc_per_htotal);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_x_after_scaler           = 0x%0x\n",
			dlg_regs.refcyc_x_after_scaler);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_after_scaler              = 0x%0x\n",
			dlg_regs.dst_y_after_scaler);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_prefetch                  = 0x%0x\n",
			dlg_regs.dst_y_prefetch);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_vm_vblank             = 0x%0x\n",
			dlg_regs.dst_y_per_vm_vblank);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_row_vblank            = 0x%0x\n",
			dlg_regs.dst_y_per_row_vblank);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_vm_flip               = 0x%0x\n",
			dlg_regs.dst_y_per_vm_flip);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_row_flip              = 0x%0x\n",
			dlg_regs.dst_y_per_row_flip);
	dml_print(
			"DML_RQ_DLG_CALC:    ref_freq_to_pix_freq            = 0x%0x\n",
			dlg_regs.ref_freq_to_pix_freq);
	dml_print(
			"DML_RQ_DLG_CALC:    vratio_prefetch                 = 0x%0x\n",
			dlg_regs.vratio_prefetch);
	dml_print(
			"DML_RQ_DLG_CALC:    vratio_prefetch_c               = 0x%0x\n",
			dlg_regs.vratio_prefetch_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_pte_group_vblank_l   = 0x%0x\n",
			dlg_regs.refcyc_per_pte_group_vblank_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_pte_group_vblank_c   = 0x%0x\n",
			dlg_regs.refcyc_per_pte_group_vblank_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_meta_chunk_vblank_l  = 0x%0x\n",
			dlg_regs.refcyc_per_meta_chunk_vblank_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_meta_chunk_vblank_c  = 0x%0x\n",
			dlg_regs.refcyc_per_meta_chunk_vblank_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_pte_group_flip_l     = 0x%0x\n",
			dlg_regs.refcyc_per_pte_group_flip_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_pte_group_flip_c     = 0x%0x\n",
			dlg_regs.refcyc_per_pte_group_flip_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_meta_chunk_flip_l    = 0x%0x\n",
			dlg_regs.refcyc_per_meta_chunk_flip_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_meta_chunk_flip_c    = 0x%0x\n",
			dlg_regs.refcyc_per_meta_chunk_flip_c);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_pte_row_nom_l         = 0x%0x\n",
			dlg_regs.dst_y_per_pte_row_nom_l);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_pte_row_nom_c         = 0x%0x\n",
			dlg_regs.dst_y_per_pte_row_nom_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_pte_group_nom_l      = 0x%0x\n",
			dlg_regs.refcyc_per_pte_group_nom_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_pte_group_nom_c      = 0x%0x\n",
			dlg_regs.refcyc_per_pte_group_nom_c);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_meta_row_nom_l        = 0x%0x\n",
			dlg_regs.dst_y_per_meta_row_nom_l);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_per_meta_row_nom_c        = 0x%0x\n",
			dlg_regs.dst_y_per_meta_row_nom_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_meta_chunk_nom_l     = 0x%0x\n",
			dlg_regs.refcyc_per_meta_chunk_nom_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_meta_chunk_nom_c     = 0x%0x\n",
			dlg_regs.refcyc_per_meta_chunk_nom_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_line_delivery_pre_l  = 0x%0x\n",
			dlg_regs.refcyc_per_line_delivery_pre_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_line_delivery_pre_c  = 0x%0x\n",
			dlg_regs.refcyc_per_line_delivery_pre_c);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_line_delivery_l      = 0x%0x\n",
			dlg_regs.refcyc_per_line_delivery_l);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_line_delivery_c      = 0x%0x\n",
			dlg_regs.refcyc_per_line_delivery_c);
	dml_print(
			"DML_RQ_DLG_CALC:    chunk_hdl_adjust_cur0           = 0x%0x\n",
			dlg_regs.chunk_hdl_adjust_cur0);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_offset_cur1               = 0x%0x\n",
			dlg_regs.dst_y_offset_cur1);
	dml_print(
			"DML_RQ_DLG_CALC:    chunk_hdl_adjust_cur1           = 0x%0x\n",
			dlg_regs.chunk_hdl_adjust_cur1);
	dml_print(
			"DML_RQ_DLG_CALC:    vready_after_vcount0            = 0x%0x\n",
			dlg_regs.vready_after_vcount0);
	dml_print(
			"DML_RQ_DLG_CALC:    dst_y_delta_drq_limit           = 0x%0x\n",
			dlg_regs.dst_y_delta_drq_limit);
	dml_print(
			"DML_RQ_DLG_CALC:    xfc_reg_transfer_delay          = 0x%0x\n",
			dlg_regs.xfc_reg_transfer_delay);
	dml_print(
			"DML_RQ_DLG_CALC:    xfc_reg_precharge_delay         = 0x%0x\n",
			dlg_regs.xfc_reg_precharge_delay);
	dml_print(
			"DML_RQ_DLG_CALC:    xfc_reg_remote_surface_flip_latency = 0x%0x\n",
			dlg_regs.xfc_reg_remote_surface_flip_latency);
	dml_print(
			"DML_RQ_DLG_CALC:    refcyc_per_vm_dmdata            = 0x%0x\n",
			dlg_regs.refcyc_per_vm_dmdata);

	dml_print("DML_RQ_DLG_CALC: =====================================\n");
}