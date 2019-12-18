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
struct pp_smu_funcs {int dummy; } ;
struct dc_debug_options {int /*<<< orphan*/  disable_dfs_bypass; } ;
struct dc_context {struct dc_bios* dc_bios; TYPE_1__* dc; } ;
struct TYPE_7__ {int smu_gpu_pll_output_freq; } ;
struct dc_bios {TYPE_4__* integrated_info; TYPE_3__ fw_info; scalar_t__ fw_info_valid; } ;
struct TYPE_6__ {int dprefclk_khz; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct clk_mgr_internal {int dprefclk_ss_divider; int ss_on_dprefclk; int dentist_vco_freq_khz; int dfs_bypass_enabled; TYPE_2__ base; scalar_t__ dprefclk_ss_percentage; scalar_t__ dfs_bypass_disp_clk; int /*<<< orphan*/ * funcs; struct pp_smu_funcs* pp_smu; } ;
struct TYPE_8__ {int dentist_vco_freq; int gpu_cap_info; } ;
struct TYPE_5__ {struct dc_debug_options debug; } ;

/* Variables and functions */
 int DFS_BYPASS_ENABLE ; 
 int /*<<< orphan*/  dce_clock_read_ss_info (struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  rv1_clk_funcs ; 
 int /*<<< orphan*/  rv1_clk_internal_funcs ; 

void rv1_clk_mgr_construct(struct dc_context *ctx, struct clk_mgr_internal *clk_mgr, struct pp_smu_funcs *pp_smu)
{
	struct dc_debug_options *debug = &ctx->dc->debug;
	struct dc_bios *bp = ctx->dc_bios;

	clk_mgr->base.ctx = ctx;
	clk_mgr->pp_smu = pp_smu;
	clk_mgr->base.funcs = &rv1_clk_funcs;
	clk_mgr->funcs = &rv1_clk_internal_funcs;

	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_divider = 1000;
	clk_mgr->ss_on_dprefclk = false;
	clk_mgr->base.dprefclk_khz = 600000;

	if (bp->integrated_info)
		clk_mgr->dentist_vco_freq_khz = bp->integrated_info->dentist_vco_freq;
	if (bp->fw_info_valid && clk_mgr->dentist_vco_freq_khz == 0) {
		clk_mgr->dentist_vco_freq_khz = bp->fw_info.smu_gpu_pll_output_freq;
		if (clk_mgr->dentist_vco_freq_khz == 0)
			clk_mgr->dentist_vco_freq_khz = 3600000;
	}

	if (!debug->disable_dfs_bypass && bp->integrated_info)
		if (bp->integrated_info->gpu_cap_info & DFS_BYPASS_ENABLE)
			clk_mgr->dfs_bypass_enabled = true;

	dce_clock_read_ss_info(clk_mgr);
}