#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dc_bios {TYPE_3__* funcs; } ;
struct TYPE_10__ {TYPE_4__* ctx; } ;
struct clk_mgr_internal {TYPE_5__ base; } ;
struct TYPE_7__ {int USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK; } ;
struct bp_set_dce_clock_parameters {int target_clock_frequency; scalar_t__ pll_id; TYPE_2__ flags; int /*<<< orphan*/  clock_type; } ;
typedef  int /*<<< orphan*/  dce_clk_params ;
struct TYPE_6__ {int /*<<< orphan*/  hw_internal_rev; } ;
struct TYPE_9__ {TYPE_1__ asic_id; struct dc_bios* dc_bios; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_dce_clock ) (struct dc_bios*,struct bp_set_dce_clock_parameters*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASICREV_IS_VEGA20_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CLOCK_SOURCE_COMBO_DISPLAY_PLL0 ; 
 scalar_t__ CLOCK_SOURCE_ID_DFS ; 
 int /*<<< orphan*/  DCECLOCK_TYPE_DPREFCLK ; 
 int /*<<< orphan*/  memset (struct bp_set_dce_clock_parameters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc_bios*,struct bp_set_dce_clock_parameters*) ; 

int dce112_set_dprefclk(struct clk_mgr_internal *clk_mgr)
{
	struct bp_set_dce_clock_parameters dce_clk_params;
	struct dc_bios *bp = clk_mgr->base.ctx->dc_bios;

	memset(&dce_clk_params, 0, sizeof(dce_clk_params));

	/*Program DP ref Clock*/
	/*VBIOS will determine DPREFCLK frequency, so we don't set it*/
	dce_clk_params.target_clock_frequency = 0;
	dce_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;
	dce_clk_params.clock_type = DCECLOCK_TYPE_DPREFCLK;
	if (!ASICREV_IS_VEGA20_P(clk_mgr->base.ctx->asic_id.hw_internal_rev))
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK =
			(dce_clk_params.pll_id ==
					CLOCK_SOURCE_COMBO_DISPLAY_PLL0);
	else
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK = false;

	bp->funcs->set_dce_clock(bp, &dce_clk_params);

	/* Returns the dp_refclk that was set */
	return dce_clk_params.target_clock_frequency;
}