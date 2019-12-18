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
struct TYPE_7__ {int /*<<< orphan*/  bw_dppclk_khz; int /*<<< orphan*/  max_supported_dppclk_khz; int /*<<< orphan*/  bw_dispclk_khz; int /*<<< orphan*/  max_supported_dispclk_khz; } ;
struct TYPE_8__ {TYPE_2__ clk; } ;
struct TYPE_9__ {TYPE_3__ dcn; } ;
struct TYPE_10__ {TYPE_4__ bw; } ;
struct dc_state {TYPE_5__ bw_ctx; } ;
struct dc_clock_config {int /*<<< orphan*/  bw_requirequired_clock_khz; int /*<<< orphan*/  current_clock_khz; int /*<<< orphan*/  min_clock_khz; int /*<<< orphan*/  max_clock_khz; } ;
struct TYPE_6__ {int /*<<< orphan*/  dppclk_khz; int /*<<< orphan*/  dispclk_khz; } ;
struct clk_mgr {TYPE_1__ clks; } ;
typedef  enum dc_clock_type { ____Placeholder_dc_clock_type } dc_clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  DCN_MINIMUM_DISPCLK_Khz ; 
 int /*<<< orphan*/  DCN_MINIMUM_DPPCLK_Khz ; 
 int DC_CLOCK_TYPE_DISPCLK ; 
 int DC_CLOCK_TYPE_DPPCLK ; 

void dcn2_get_clock(struct clk_mgr *clk_mgr,
		struct dc_state *context,
			enum dc_clock_type clock_type,
			struct dc_clock_config *clock_cfg)
{

	if (clock_type == DC_CLOCK_TYPE_DISPCLK) {
		clock_cfg->max_clock_khz = context->bw_ctx.bw.dcn.clk.max_supported_dispclk_khz;
		clock_cfg->min_clock_khz = DCN_MINIMUM_DISPCLK_Khz;
		clock_cfg->current_clock_khz = clk_mgr->clks.dispclk_khz;
		clock_cfg->bw_requirequired_clock_khz = context->bw_ctx.bw.dcn.clk.bw_dispclk_khz;
	}
	if (clock_type == DC_CLOCK_TYPE_DPPCLK) {
		clock_cfg->max_clock_khz = context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz;
		clock_cfg->min_clock_khz = DCN_MINIMUM_DPPCLK_Khz;
		clock_cfg->current_clock_khz = clk_mgr->clks.dppclk_khz;
		clock_cfg->bw_requirequired_clock_khz = context->bw_ctx.bw.dcn.clk.bw_dppclk_khz;
	}
}