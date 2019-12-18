#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bp; struct dc_context* ctx; int /*<<< orphan*/ * funcs; } ;
struct dce110_timing_generator {int min_h_blank; int min_h_front_porch; int min_h_back_porch; scalar_t__ max_v_total; scalar_t__ max_h_total; TYPE_1__ base; int /*<<< orphan*/  controller_id; } ;
struct dc_context {int /*<<< orphan*/  dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLLER_ID_UNDERLAY0 ; 
 scalar_t__ CRTC_H_TOTAL__CRTC_H_TOTAL_MASK ; 
 scalar_t__ CRTC_V_TOTAL__CRTC_V_TOTAL_MASK ; 
 int /*<<< orphan*/  dce110_tg_v_funcs ; 

void dce110_timing_generator_v_construct(
	struct dce110_timing_generator *tg110,
	struct dc_context *ctx)
{
	tg110->controller_id = CONTROLLER_ID_UNDERLAY0;

	tg110->base.funcs = &dce110_tg_v_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_total = CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1;
	tg110->max_v_total = CRTC_V_TOTAL__CRTC_V_TOTAL_MASK + 1;

	tg110->min_h_blank = 56;
	tg110->min_h_front_porch = 4;
	tg110->min_h_back_porch = 4;
}