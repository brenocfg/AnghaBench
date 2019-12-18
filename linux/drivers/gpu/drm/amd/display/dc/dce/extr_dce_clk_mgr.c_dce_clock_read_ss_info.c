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
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct spread_spectrum_info {scalar_t__ spread_spectrum_percentage; TYPE_5__ type; int /*<<< orphan*/  spread_percentage_divider; TYPE_3__ member_0; } ;
struct TYPE_7__ {TYPE_1__* ctx; } ;
struct dce_clk_mgr {int ss_on_dprefclk; scalar_t__ dprefclk_ss_percentage; int /*<<< orphan*/  dprefclk_ss_divider; TYPE_2__ base; } ;
struct dc_bios {TYPE_4__* funcs; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_9__ {int (* get_ss_entry_number ) (struct dc_bios*,int /*<<< orphan*/ ) ;int (* get_spread_spectrum_info ) (struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spread_spectrum_info*) ;} ;
struct TYPE_6__ {struct dc_bios* dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  AS_SIGNAL_TYPE_GPU_PLL ; 
 int BP_RESULT_OK ; 
 int stub1 (struct dc_bios*,int /*<<< orphan*/ ) ; 
 int stub2 (struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spread_spectrum_info*) ; 
 int stub3 (struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spread_spectrum_info*) ; 

void dce_clock_read_ss_info(struct dce_clk_mgr *clk_mgr_dce)
{
	struct dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;
	int ss_info_num = bp->funcs->get_ss_entry_number(
			bp, AS_SIGNAL_TYPE_GPU_PLL);

	if (ss_info_num) {
		struct spread_spectrum_info info = { { 0 } };
		enum bp_result result = bp->funcs->get_spread_spectrum_info(
				bp, AS_SIGNAL_TYPE_GPU_PLL, 0, &info);

		/* Based on VBIOS, VBIOS will keep entry for GPU PLL SS
		 * even if SS not enabled and in that case
		 * SSInfo.spreadSpectrumPercentage !=0 would be sign
		 * that SS is enabled
		 */
		if (result == BP_RESULT_OK &&
				info.spread_spectrum_percentage != 0) {
			clk_mgr_dce->ss_on_dprefclk = true;
			clk_mgr_dce->dprefclk_ss_divider = info.spread_percentage_divider;

			if (info.type.CENTER_MODE == 0) {
				/* TODO: Currently for DP Reference clock we
				 * need only SS percentage for
				 * downspread */
				clk_mgr_dce->dprefclk_ss_percentage =
						info.spread_spectrum_percentage;
			}

			return;
		}

		result = bp->funcs->get_spread_spectrum_info(
				bp, AS_SIGNAL_TYPE_DISPLAY_PORT, 0, &info);

		/* Based on VBIOS, VBIOS will keep entry for DPREFCLK SS
		 * even if SS not enabled and in that case
		 * SSInfo.spreadSpectrumPercentage !=0 would be sign
		 * that SS is enabled
		 */
		if (result == BP_RESULT_OK &&
				info.spread_spectrum_percentage != 0) {
			clk_mgr_dce->ss_on_dprefclk = true;
			clk_mgr_dce->dprefclk_ss_divider = info.spread_percentage_divider;

			if (info.type.CENTER_MODE == 0) {
				/* Currently for DP Reference clock we
				 * need only SS percentage for
				 * downspread */
				clk_mgr_dce->dprefclk_ss_percentage =
						info.spread_spectrum_percentage;
			}
		}
	}
}