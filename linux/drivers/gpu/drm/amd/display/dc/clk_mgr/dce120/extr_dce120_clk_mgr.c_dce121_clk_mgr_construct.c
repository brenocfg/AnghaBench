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
struct dc_context {TYPE_2__* dc; } ;
struct TYPE_3__ {int dprefclk_khz; } ;
struct clk_mgr_internal {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce120_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  dce121_clock_patch_xgmi_ss_info (struct clk_mgr_internal*) ; 
 scalar_t__ dce121_xgmi_enabled (int /*<<< orphan*/ ) ; 

void dce121_clk_mgr_construct(struct dc_context *ctx, struct clk_mgr_internal *clk_mgr)
{
	dce120_clk_mgr_construct(ctx, clk_mgr);
	clk_mgr->base.dprefclk_khz = 625000;

	/*
	 * The xGMI enabled info is used to determine if audio and display
	 * clocks need to be adjusted with the WAFL link's SS info.
	 */
	if (dce121_xgmi_enabled(ctx->dc->hwseq))
		dce121_clock_patch_xgmi_ss_info(clk_mgr);

}