#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * init_pipes; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  disable_vga; int /*<<< orphan*/ * dsc_pg_control; int /*<<< orphan*/  hubp_pg_control; int /*<<< orphan*/  dpp_pg_control; int /*<<< orphan*/  enable_power_gating_plane; int /*<<< orphan*/  plane_atomic_disable; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  init_blank; int /*<<< orphan*/  set_flip_control_gsl; int /*<<< orphan*/  update_mpcc; int /*<<< orphan*/  reset_hw_ctx_wrap; int /*<<< orphan*/  setup_vupdate_interrupt; int /*<<< orphan*/  enable_stream_gating; int /*<<< orphan*/  disable_stream_gating; int /*<<< orphan*/  init_vm_ctx; int /*<<< orphan*/  init_sys_ctx; int /*<<< orphan*/  disable_stream; int /*<<< orphan*/  enable_stream; int /*<<< orphan*/  program_dmdata_engine; int /*<<< orphan*/  dmdata_status_done; int /*<<< orphan*/  blank_pixel_data; int /*<<< orphan*/  update_odm; int /*<<< orphan*/  program_output_csc; int /*<<< orphan*/  disable_writeback; int /*<<< orphan*/  enable_writeback; int /*<<< orphan*/  update_bandwidth; int /*<<< orphan*/  prepare_bandwidth; int /*<<< orphan*/  optimize_bandwidth; int /*<<< orphan*/  pipe_control_lock_global; int /*<<< orphan*/  pipe_control_lock; int /*<<< orphan*/  apply_ctx_for_surface; int /*<<< orphan*/  set_output_transfer_func; int /*<<< orphan*/  set_input_transfer_func; int /*<<< orphan*/  program_triplebuffer; int /*<<< orphan*/  enable_stream_timing; int /*<<< orphan*/  update_plane_addr; int /*<<< orphan*/  unblank_stream; } ;
struct dc {TYPE_2__ hwss; TYPE_1__* ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  dce_environment; } ;

/* Variables and functions */
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcn10_hw_sequencer_construct (struct dc*) ; 
 int /*<<< orphan*/  dcn20_apply_ctx_for_surface ; 
 int /*<<< orphan*/  dcn20_blank_pixel_data ; 
 int /*<<< orphan*/  dcn20_disable_plane ; 
 int /*<<< orphan*/  dcn20_disable_stream ; 
 int /*<<< orphan*/  dcn20_disable_stream_gating ; 
 int /*<<< orphan*/  dcn20_disable_vga ; 
 int /*<<< orphan*/  dcn20_disable_writeback ; 
 int /*<<< orphan*/  dcn20_dmdata_status_done ; 
 int /*<<< orphan*/  dcn20_dpp_pg_control ; 
 int /*<<< orphan*/ * dcn20_dsc_pg_control ; 
 int /*<<< orphan*/  dcn20_enable_power_gating_plane ; 
 int /*<<< orphan*/  dcn20_enable_stream ; 
 int /*<<< orphan*/  dcn20_enable_stream_gating ; 
 int /*<<< orphan*/  dcn20_enable_stream_timing ; 
 int /*<<< orphan*/  dcn20_enable_writeback ; 
 int /*<<< orphan*/  dcn20_fpga_init_hw ; 
 int /*<<< orphan*/  dcn20_hubp_pg_control ; 
 int /*<<< orphan*/  dcn20_init_blank ; 
 int /*<<< orphan*/  dcn20_init_sys_ctx ; 
 int /*<<< orphan*/  dcn20_init_vm_ctx ; 
 int /*<<< orphan*/  dcn20_optimize_bandwidth ; 
 int /*<<< orphan*/  dcn20_pipe_control_lock ; 
 int /*<<< orphan*/  dcn20_pipe_control_lock_global ; 
 int /*<<< orphan*/  dcn20_plane_atomic_disable ; 
 int /*<<< orphan*/  dcn20_prepare_bandwidth ; 
 int /*<<< orphan*/  dcn20_program_dmdata_engine ; 
 int /*<<< orphan*/  dcn20_program_output_csc ; 
 int /*<<< orphan*/  dcn20_program_tripleBuffer ; 
 int /*<<< orphan*/  dcn20_reset_hw_ctx_wrap ; 
 int /*<<< orphan*/  dcn20_set_flip_control_gsl ; 
 int /*<<< orphan*/  dcn20_set_input_transfer_func ; 
 int /*<<< orphan*/  dcn20_set_output_transfer_func ; 
 int /*<<< orphan*/  dcn20_setup_vupdate_interrupt ; 
 int /*<<< orphan*/  dcn20_unblank_stream ; 
 int /*<<< orphan*/  dcn20_update_bandwidth ; 
 int /*<<< orphan*/  dcn20_update_mpcc ; 
 int /*<<< orphan*/  dcn20_update_odm ; 
 int /*<<< orphan*/  dcn20_update_plane_addr ; 

void dcn20_hw_sequencer_construct(struct dc *dc)
{
	dcn10_hw_sequencer_construct(dc);
	dc->hwss.unblank_stream = dcn20_unblank_stream;
	dc->hwss.update_plane_addr = dcn20_update_plane_addr;
	dc->hwss.enable_stream_timing = dcn20_enable_stream_timing;
	dc->hwss.program_triplebuffer = dcn20_program_tripleBuffer;
	dc->hwss.set_input_transfer_func = dcn20_set_input_transfer_func;
	dc->hwss.set_output_transfer_func = dcn20_set_output_transfer_func;
	dc->hwss.apply_ctx_for_surface = dcn20_apply_ctx_for_surface;
	dc->hwss.pipe_control_lock = dcn20_pipe_control_lock;
	dc->hwss.pipe_control_lock_global = dcn20_pipe_control_lock_global;
	dc->hwss.optimize_bandwidth = dcn20_optimize_bandwidth;
	dc->hwss.prepare_bandwidth = dcn20_prepare_bandwidth;
	dc->hwss.update_bandwidth = dcn20_update_bandwidth;
	dc->hwss.enable_writeback = dcn20_enable_writeback;
	dc->hwss.disable_writeback = dcn20_disable_writeback;
	dc->hwss.program_output_csc = dcn20_program_output_csc;
	dc->hwss.update_odm = dcn20_update_odm;
	dc->hwss.blank_pixel_data = dcn20_blank_pixel_data;
	dc->hwss.dmdata_status_done = dcn20_dmdata_status_done;
	dc->hwss.program_dmdata_engine = dcn20_program_dmdata_engine;
	dc->hwss.enable_stream = dcn20_enable_stream;
	dc->hwss.disable_stream = dcn20_disable_stream;
	dc->hwss.init_sys_ctx = dcn20_init_sys_ctx;
	dc->hwss.init_vm_ctx = dcn20_init_vm_ctx;
	dc->hwss.disable_stream_gating = dcn20_disable_stream_gating;
	dc->hwss.enable_stream_gating = dcn20_enable_stream_gating;
	dc->hwss.setup_vupdate_interrupt = dcn20_setup_vupdate_interrupt;
	dc->hwss.reset_hw_ctx_wrap = dcn20_reset_hw_ctx_wrap;
	dc->hwss.update_mpcc = dcn20_update_mpcc;
	dc->hwss.set_flip_control_gsl = dcn20_set_flip_control_gsl;
	dc->hwss.init_blank = dcn20_init_blank;
	dc->hwss.disable_plane = dcn20_disable_plane;
	dc->hwss.plane_atomic_disable = dcn20_plane_atomic_disable;
	dc->hwss.enable_power_gating_plane = dcn20_enable_power_gating_plane;
	dc->hwss.dpp_pg_control = dcn20_dpp_pg_control;
	dc->hwss.hubp_pg_control = dcn20_hubp_pg_control;
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	dc->hwss.dsc_pg_control = dcn20_dsc_pg_control;
#else
	dc->hwss.dsc_pg_control = NULL;
#endif
	dc->hwss.disable_vga = dcn20_disable_vga;

	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {
		dc->hwss.init_hw = dcn20_fpga_init_hw;
		dc->hwss.init_pipes = NULL;
	}


}