#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pp_smu_funcs {int dummy; } ;
struct fixed31_32 {int value; } ;
struct dccg {int dummy; } ;
struct dc_context {int /*<<< orphan*/  dce_environment; } ;
struct TYPE_4__ {int dprefclk_khz; TYPE_2__* funcs; struct dc_context* ctx; } ;
struct clk_mgr_internal {int dprefclk_ss_divider; int ss_on_dprefclk; int dentist_vco_freq_khz; int dfs_bypass_enabled; TYPE_1__ base; TYPE_3__* clk_mgr_mask; scalar_t__ dprefclk_ss_percentage; scalar_t__ dfs_bypass_disp_clk; struct dccg* dccg; int /*<<< orphan*/ * clk_mgr_shift; int /*<<< orphan*/ * regs; struct pp_smu_funcs* pp_smu; } ;
struct TYPE_6__ {int FbMult_int; int FbMult_frac; } ;
struct TYPE_5__ {int /*<<< orphan*/  update_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK3_CLK2_DFS_CNTL ; 
 int /*<<< orphan*/  CLK3_CLK_PLL_REQ ; 
 int DENTIST_DIVIDER_RANGE_SCALE_FACTOR ; 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 void* REG_READ (int /*<<< orphan*/ ) ; 
 TYPE_3__ clk_mgr_mask ; 
 int /*<<< orphan*/  clk_mgr_regs ; 
 int /*<<< orphan*/  clk_mgr_shift ; 
 int dc_fixpt_floor (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_from_int (int) ; 
 struct fixed31_32 dc_fixpt_mul_int (struct fixed31_32,int) ; 
 int /*<<< orphan*/  dce_clock_read_ss_info (struct clk_mgr_internal*) ; 
 TYPE_2__ dcn2_funcs ; 
 int /*<<< orphan*/  dcn2_update_clocks_fpga ; 
 int dentist_get_divider_from_did (int) ; 

void dcn20_clk_mgr_construct(
		struct dc_context *ctx,
		struct clk_mgr_internal *clk_mgr,
		struct pp_smu_funcs *pp_smu,
		struct dccg *dccg)
{
	clk_mgr->base.ctx = ctx;
	clk_mgr->pp_smu = pp_smu;
	clk_mgr->base.funcs = &dcn2_funcs;
	clk_mgr->regs = &clk_mgr_regs;
	clk_mgr->clk_mgr_shift = &clk_mgr_shift;
	clk_mgr->clk_mgr_mask = &clk_mgr_mask;

	clk_mgr->dccg = dccg;
	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_divider = 1000;
	clk_mgr->ss_on_dprefclk = false;

	clk_mgr->base.dprefclk_khz = 700000; // 700 MHz planned if VCO is 3.85 GHz, will be retrieved

	if (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) {
		dcn2_funcs.update_clocks = dcn2_update_clocks_fpga;
		clk_mgr->dentist_vco_freq_khz = 3850000;

	} else {
		/* DFS Slice 2 should be used for DPREFCLK */
		int dprefclk_did = REG_READ(CLK3_CLK2_DFS_CNTL);
		/* Convert DPREFCLK DFS Slice DID to actual divider*/
		int target_div = dentist_get_divider_from_did(dprefclk_did);

		/* get FbMult value */
		uint32_t pll_req_reg = REG_READ(CLK3_CLK_PLL_REQ);
		struct fixed31_32 pll_req;

		/* set up a fixed-point number
		 * this works because the int part is on the right edge of the register
		 * and the frac part is on the left edge
		 */

		pll_req = dc_fixpt_from_int(pll_req_reg & clk_mgr->clk_mgr_mask->FbMult_int);
		pll_req.value |= pll_req_reg & clk_mgr->clk_mgr_mask->FbMult_frac;

		/* multiply by REFCLK period */
		pll_req = dc_fixpt_mul_int(pll_req, 100000);

		/* integer part is now VCO frequency in kHz */
		clk_mgr->dentist_vco_freq_khz = dc_fixpt_floor(pll_req);

		/* in case we don't get a value from the register, use default */
		if (clk_mgr->dentist_vco_freq_khz == 0)
			clk_mgr->dentist_vco_freq_khz = 3850000;

		/* Calculate the DPREFCLK in kHz.*/
		clk_mgr->base.dprefclk_khz = (DENTIST_DIVIDER_RANGE_SCALE_FACTOR
			* clk_mgr->dentist_vco_freq_khz) / target_div;
	}
	//Integrated_info table does not exist on dGPU projects so should not be referenced
	//anywhere in code for dGPUs.
	//Also there is no plan for now that DFS BYPASS will be used on NV10/12/14.
	clk_mgr->dfs_bypass_enabled = false;

	dce_clock_read_ss_info(clk_mgr);
}