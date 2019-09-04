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
typedef  size_t uint32_t ;
struct pll_settings {int dummy; } ;
struct pixel_clk_params {size_t controller_id; } ;
struct pipe_ctx {TYPE_3__* stream; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_2__ res_ctx; } ;
struct dc {struct dc_state* current_state; } ;
struct clock_source {TYPE_1__* ctx; } ;
struct TYPE_6__ {size_t phy_pix_clk; } ;
struct TYPE_4__ {struct dc* dc; } ;

/* Variables and functions */
 size_t CONTROLLER_ID_D0 ; 

__attribute__((used)) static uint32_t dce110_get_dp_pixel_rate_from_combo_phy_pll(
	struct clock_source *cs,
	struct pixel_clk_params *pix_clk_params,
	struct pll_settings *pll_settings)
{
	uint32_t inst = pix_clk_params->controller_id - CONTROLLER_ID_D0;
	struct dc *dc_core = cs->ctx->dc;
	struct dc_state *context = dc_core->current_state;
	struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[inst];

	/* This function need separate to different DCE version, before separate, just use pixel clock */
	return pipe_ctx->stream->phy_pix_clk;
}