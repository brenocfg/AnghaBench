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
struct TYPE_10__ {scalar_t__ CENTER_MODE; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct spread_spectrum_info {scalar_t__ spread_spectrum_percentage; TYPE_5__ type; int /*<<< orphan*/  spread_percentage_divider; TYPE_1__ member_0; } ;
struct TYPE_8__ {TYPE_2__* ctx; } ;
struct dce_clk_mgr {int xgmi_enabled; int ss_on_dprefclk; scalar_t__ dprefclk_ss_percentage; int /*<<< orphan*/  dprefclk_ss_divider; TYPE_3__ base; } ;
struct dc_bios {TYPE_4__* funcs; } ;
struct clk_mgr {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_9__ {int (* get_spread_spectrum_info ) (struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spread_spectrum_info*) ;} ;
struct TYPE_7__ {struct dc_bios* dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_SIGNAL_TYPE_XGMI ; 
 int BP_RESULT_OK ; 
 struct dce_clk_mgr* TO_DCE_CLK_MGR (struct clk_mgr*) ; 
 int stub1 (struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spread_spectrum_info*) ; 

void dce121_clock_patch_xgmi_ss_info(struct clk_mgr *clk_mgr)
{
	struct dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	enum bp_result result;
	struct spread_spectrum_info info = { { 0 } };
	struct dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;

	clk_mgr_dce->xgmi_enabled = false;

	result = bp->funcs->get_spread_spectrum_info(bp, AS_SIGNAL_TYPE_XGMI,
						     0, &info);
	if (result == BP_RESULT_OK && info.spread_spectrum_percentage != 0) {
		clk_mgr_dce->xgmi_enabled = true;
		clk_mgr_dce->ss_on_dprefclk = true;
		clk_mgr_dce->dprefclk_ss_divider =
				info.spread_percentage_divider;

		if (info.type.CENTER_MODE == 0) {
			/* Currently for DP Reference clock we
			 * need only SS percentage for
			 * downspread */
			clk_mgr_dce->dprefclk_ss_percentage =
					info.spread_spectrum_percentage;
		}
	}
}