#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dc_debug_options {int /*<<< orphan*/  disable_dfs_bypass; } ;
struct TYPE_11__ {int smu_gpu_pll_output_freq; } ;
struct dc_bios {TYPE_7__* integrated_info; TYPE_4__ fw_info; } ;
struct TYPE_10__ {TYPE_2__* ctx; } ;
struct clk_mgr_internal {int dentist_vco_freq_khz; int dfs_bypass_enabled; TYPE_5__* max_clks_by_state; TYPE_3__ base; } ;
typedef  enum dm_pp_clocks_state { ____Placeholder_dm_pp_clocks_state } dm_pp_clocks_state ;
struct TYPE_14__ {int dentist_vco_freq; int gpu_cap_info; TYPE_6__* disp_clk_voltage; } ;
struct TYPE_13__ {int max_supported_clk; } ;
struct TYPE_12__ {int display_clk_khz; } ;
struct TYPE_9__ {struct dc_bios* dc_bios; TYPE_1__* dc; } ;
struct TYPE_8__ {struct dc_debug_options debug; } ;

/* Variables and functions */
 int DFS_BYPASS_ENABLE ; 
 int DM_PP_CLOCKS_STATE_INVALID ; 
 int DM_PP_CLOCKS_STATE_LOW ; 
 int DM_PP_CLOCKS_STATE_NOMINAL ; 
 int DM_PP_CLOCKS_STATE_PERFORMANCE ; 
 int DM_PP_CLOCKS_STATE_ULTRA_LOW ; 
 int NUMBER_OF_DISP_CLK_VOLTAGE ; 

__attribute__((used)) static void dce_clock_read_integrated_info(struct clk_mgr_internal *clk_mgr_dce)
{
	struct dc_debug_options *debug = &clk_mgr_dce->base.ctx->dc->debug;
	struct dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;
	int i;

	if (bp->integrated_info)
		clk_mgr_dce->dentist_vco_freq_khz = bp->integrated_info->dentist_vco_freq;
	if (clk_mgr_dce->dentist_vco_freq_khz == 0) {
		clk_mgr_dce->dentist_vco_freq_khz = bp->fw_info.smu_gpu_pll_output_freq;
		if (clk_mgr_dce->dentist_vco_freq_khz == 0)
			clk_mgr_dce->dentist_vco_freq_khz = 3600000;
	}

	/*update the maximum display clock for each power state*/
	for (i = 0; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) {
		enum dm_pp_clocks_state clk_state = DM_PP_CLOCKS_STATE_INVALID;

		switch (i) {
		case 0:
			clk_state = DM_PP_CLOCKS_STATE_ULTRA_LOW;
			break;

		case 1:
			clk_state = DM_PP_CLOCKS_STATE_LOW;
			break;

		case 2:
			clk_state = DM_PP_CLOCKS_STATE_NOMINAL;
			break;

		case 3:
			clk_state = DM_PP_CLOCKS_STATE_PERFORMANCE;
			break;

		default:
			clk_state = DM_PP_CLOCKS_STATE_INVALID;
			break;
		}

		/*Do not allow bad VBIOS/SBIOS to override with invalid values,
		 * check for > 100MHz*/
		if (bp->integrated_info)
			if (bp->integrated_info->disp_clk_voltage[i].max_supported_clk >= 100000)
				clk_mgr_dce->max_clks_by_state[clk_state].display_clk_khz =
					bp->integrated_info->disp_clk_voltage[i].max_supported_clk;
	}

	if (!debug->disable_dfs_bypass && bp->integrated_info)
		if (bp->integrated_info->gpu_cap_info & DFS_BYPASS_ENABLE)
			clk_mgr_dce->dfs_bypass_enabled = true;
}