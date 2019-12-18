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
struct TYPE_5__ {scalar_t__ phyclk_khz; scalar_t__ fclk_khz; scalar_t__ dcfclk_deep_sleep_khz; scalar_t__ socclk_khz; scalar_t__ dppclk_khz; scalar_t__ max_supported_dppclk_khz; scalar_t__ dramclk_khz; scalar_t__ dcfclk_khz; scalar_t__ dispclk_khz; } ;
struct TYPE_6__ {TYPE_1__ clk; } ;
struct TYPE_7__ {TYPE_2__ dcn; } ;
struct TYPE_8__ {TYPE_3__ bw; } ;
struct dc_state {TYPE_4__ bw_ctx; } ;
struct AsicStateEx {unsigned int displayClock; unsigned int engineClock; unsigned int memoryClock; unsigned int maxSupportedDppClock; unsigned int dppClock; unsigned int socClock; unsigned int dcfClockDeepSleep; unsigned int fClock; unsigned int phyClock; } ;

/* Variables and functions */

void get_clock_requirements_for_state(struct dc_state *state, struct AsicStateEx *info)
{
	info->displayClock				= (unsigned int)state->bw_ctx.bw.dcn.clk.dispclk_khz;
	info->engineClock				= (unsigned int)state->bw_ctx.bw.dcn.clk.dcfclk_khz;
	info->memoryClock				= (unsigned int)state->bw_ctx.bw.dcn.clk.dramclk_khz;
	info->maxSupportedDppClock		= (unsigned int)state->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz;
	info->dppClock					= (unsigned int)state->bw_ctx.bw.dcn.clk.dppclk_khz;
	info->socClock					= (unsigned int)state->bw_ctx.bw.dcn.clk.socclk_khz;
	info->dcfClockDeepSleep			= (unsigned int)state->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz;
	info->fClock					= (unsigned int)state->bw_ctx.bw.dcn.clk.fclk_khz;
	info->phyClock					= (unsigned int)state->bw_ctx.bw.dcn.clk.phyclk_khz;
}