#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dc_state {int dummy; } ;
struct dc {int dummy; } ;

/* Variables and functions */

void context_clock_trace(
		struct dc *dc,
		struct dc_state *context)
{
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	DC_LOGGER_INIT(dc->ctx->logger);
	CLOCK_TRACE("Current: dispclk_khz:%d  max_dppclk_khz:%d  dcfclk_khz:%d\n"
			"dcfclk_deep_sleep_khz:%d  fclk_khz:%d  socclk_khz:%d\n",
			context->bw.dcn.clk.dispclk_khz,
			context->bw.dcn.clk.dppclk_khz,
			context->bw.dcn.clk.dcfclk_khz,
			context->bw.dcn.clk.dcfclk_deep_sleep_khz,
			context->bw.dcn.clk.fclk_khz,
			context->bw.dcn.clk.socclk_khz);
	CLOCK_TRACE("Calculated: dispclk_khz:%d  max_dppclk_khz:%d  dcfclk_khz:%d\n"
			"dcfclk_deep_sleep_khz:%d  fclk_khz:%d  socclk_khz:%d\n",
			context->bw.dcn.clk.dispclk_khz,
			context->bw.dcn.clk.dppclk_khz,
			context->bw.dcn.clk.dcfclk_khz,
			context->bw.dcn.clk.dcfclk_deep_sleep_khz,
			context->bw.dcn.clk.fclk_khz,
			context->bw.dcn.clk.socclk_khz);
#endif
}