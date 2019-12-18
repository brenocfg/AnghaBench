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
struct pp_smu_wm_range_sets {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_wm_ranges ) (int /*<<< orphan*/ *,struct pp_smu_wm_range_sets*) ;int /*<<< orphan*/  (* get_dpm_clock_table ) (int /*<<< orphan*/ *,struct dpm_clocks*) ;} ;
struct pp_smu_funcs {TYPE_2__ rn_funcs; } ;
struct dpm_clocks {int /*<<< orphan*/  member_0; } ;
struct dccg {int dummy; } ;
struct dc_debug_options {int /*<<< orphan*/  disable_48mhz_pwrdwn; int /*<<< orphan*/  disable_pplib_wm_range; } ;
struct dc_context {int /*<<< orphan*/  asic_id; int /*<<< orphan*/  dce_environment; TYPE_1__* dc; } ;
struct clk_state_registers_and_bypass {int dprefclk; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int dprefclk_khz; int /*<<< orphan*/ * bw_params; TYPE_4__* funcs; struct dc_context* ctx; } ;
struct clk_mgr_internal {int dprefclk_ss_divider; int ss_on_dprefclk; int dfs_ref_freq_khz; int dentist_vco_freq_khz; TYPE_3__ base; int /*<<< orphan*/  smu_ver; scalar_t__ dprefclk_ss_percentage; scalar_t__ dfs_bypass_disp_clk; struct dccg* dccg; struct pp_smu_funcs* pp_smu; } ;
struct clk_log_info {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  update_clocks; } ;
struct TYPE_5__ {struct dc_debug_options debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_watermark_ranges (int /*<<< orphan*/ *,struct pp_smu_wm_range_sets*) ; 
 int /*<<< orphan*/  clk_mgr_helper_populate_bw_params (int /*<<< orphan*/ *,struct dpm_clocks*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dce_clock_read_ss_info (struct clk_mgr_internal*) ; 
 TYPE_4__ dcn21_funcs ; 
 int /*<<< orphan*/  dcn2_update_clocks_fpga ; 
 int get_vco_frequency_from_reg (struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  rn_bw_params ; 
 int /*<<< orphan*/  rn_dump_clk_registers (struct clk_state_registers_and_bypass*,TYPE_3__*,struct clk_log_info*) ; 
 int /*<<< orphan*/  rn_vbios_smu_enable_48mhz_tmdp_refclk_pwrdwn (struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  rn_vbios_smu_get_smu_version (struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct dpm_clocks*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct pp_smu_wm_range_sets*) ; 

void rn_clk_mgr_construct(
		struct dc_context *ctx,
		struct clk_mgr_internal *clk_mgr,
		struct pp_smu_funcs *pp_smu,
		struct dccg *dccg)
{
	struct dc_debug_options *debug = &ctx->dc->debug;
	struct dpm_clocks clock_table = { 0 };
	struct clk_state_registers_and_bypass s = { 0 };

	clk_mgr->base.ctx = ctx;
	clk_mgr->base.funcs = &dcn21_funcs;

	clk_mgr->pp_smu = pp_smu;

	clk_mgr->dccg = dccg;
	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_divider = 1000;
	clk_mgr->ss_on_dprefclk = false;
	clk_mgr->dfs_ref_freq_khz = 48000;

	clk_mgr->smu_ver = rn_vbios_smu_get_smu_version(clk_mgr);

	if (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) {
		dcn21_funcs.update_clocks = dcn2_update_clocks_fpga;
		clk_mgr->dentist_vco_freq_khz = 3600000;
		clk_mgr->base.dprefclk_khz = 600000;
	} else {
		struct clk_log_info log_info = {0};

		/* TODO: Check we get what we expect during bringup */
		clk_mgr->dentist_vco_freq_khz = get_vco_frequency_from_reg(clk_mgr);

		/* in case we don't get a value from the register, use default */
		if (clk_mgr->dentist_vco_freq_khz == 0)
			clk_mgr->dentist_vco_freq_khz = 3600000;

		rn_dump_clk_registers(&s, &clk_mgr->base, &log_info);
		clk_mgr->base.dprefclk_khz = s.dprefclk;

		if (clk_mgr->base.dprefclk_khz != 600000) {
			clk_mgr->base.dprefclk_khz = 600000;
			ASSERT(1); //TODO: Renoir follow up.
		}

		/* in case we don't get a value from the register, use default */
		if (clk_mgr->base.dprefclk_khz == 0)
			clk_mgr->base.dprefclk_khz = 600000;
	}

	dce_clock_read_ss_info(clk_mgr);

	clk_mgr->base.bw_params = &rn_bw_params;

	if (pp_smu) {
		pp_smu->rn_funcs.get_dpm_clock_table(&pp_smu->rn_funcs.pp_smu, &clock_table);
		clk_mgr_helper_populate_bw_params(clk_mgr->base.bw_params, &clock_table, &ctx->asic_id);
	}

	/*
	 * Notify SMU which set of WM should be selected for different ranges of fclk
	 * On Renoir there is a maximumum of 4 DF pstates supported, could be less
	 * depending on DDR speed and fused maximum fclk.
	 */
	if (!debug->disable_pplib_wm_range) {
		struct pp_smu_wm_range_sets ranges = {0};

		build_watermark_ranges(clk_mgr->base.bw_params, &ranges);

		/* Notify PP Lib/SMU which Watermarks to use for which clock ranges */
		if (pp_smu && pp_smu->rn_funcs.set_wm_ranges)
			pp_smu->rn_funcs.set_wm_ranges(&pp_smu->rn_funcs.pp_smu, &ranges);
	}

	/* enable powerfeatures when displaycount goes to 0 */
	if (!debug->disable_48mhz_pwrdwn)
		rn_vbios_smu_enable_48mhz_tmdp_refclk_pwrdwn(clk_mgr);
}