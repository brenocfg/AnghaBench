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
struct TYPE_7__ {int /*<<< orphan*/  socclk_khz; int /*<<< orphan*/  fclk_khz; int /*<<< orphan*/  dcfclk_deep_sleep_khz; int /*<<< orphan*/  dcfclk_khz; int /*<<< orphan*/  dppclk_khz; int /*<<< orphan*/  dispclk_khz; } ;
struct TYPE_8__ {TYPE_2__ clk; } ;
struct TYPE_9__ {TYPE_3__ dcn; } ;
struct TYPE_10__ {TYPE_4__ bw; } ;
struct dc_state {TYPE_5__ bw_ctx; } ;
struct dc {TYPE_1__* ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 

void context_clock_trace(
		struct dc *dc,
		struct dc_state *context)
{
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	DC_LOGGER_INIT(dc->ctx->logger);
	CLOCK_TRACE("Current: dispclk_khz:%d  max_dppclk_khz:%d  dcfclk_khz:%d\n"
			"dcfclk_deep_sleep_khz:%d  fclk_khz:%d  socclk_khz:%d\n",
			context->bw_ctx.bw.dcn.clk.dispclk_khz,
			context->bw_ctx.bw.dcn.clk.dppclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
			context->bw_ctx.bw.dcn.clk.fclk_khz,
			context->bw_ctx.bw.dcn.clk.socclk_khz);
	CLOCK_TRACE("Calculated: dispclk_khz:%d  max_dppclk_khz:%d  dcfclk_khz:%d\n"
			"dcfclk_deep_sleep_khz:%d  fclk_khz:%d  socclk_khz:%d\n",
			context->bw_ctx.bw.dcn.clk.dispclk_khz,
			context->bw_ctx.bw.dcn.clk.dppclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
			context->bw_ctx.bw.dcn.clk.fclk_khz,
			context->bw_ctx.bw.dcn.clk.socclk_khz);
#endif
}