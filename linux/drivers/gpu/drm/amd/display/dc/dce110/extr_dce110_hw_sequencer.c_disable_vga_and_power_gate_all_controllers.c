#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timing_generator {TYPE_1__* funcs; } ;
struct dc_context {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* disable_plane ) (struct dc*,TYPE_6__*) ;} ;
struct dc {TYPE_5__* current_state; TYPE_3__ hwss; TYPE_2__* res_pool; struct dc_context* ctx; } ;
struct TYPE_12__ {int pipe_idx; } ;
struct TYPE_10__ {TYPE_6__* pipe_ctx; } ;
struct TYPE_11__ {TYPE_4__ res_ctx; } ;
struct TYPE_8__ {int timing_generator_count; int pipe_count; struct timing_generator** timing_generators; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* disable_vga ) (struct timing_generator*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  enable_display_pipe_clock_gating (struct dc_context*,int) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,TYPE_6__*) ; 

__attribute__((used)) static void disable_vga_and_power_gate_all_controllers(
		struct dc *dc)
{
	int i;
	struct timing_generator *tg;
	struct dc_context *ctx = dc->ctx;

	for (i = 0; i < dc->res_pool->timing_generator_count; i++) {
		tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->disable_vga)
			tg->funcs->disable_vga(tg);
	}
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		/* Enable CLOCK gating for each pipe BEFORE controller
		 * powergating. */
		enable_display_pipe_clock_gating(ctx,
				true);

		dc->current_state->res_ctx.pipe_ctx[i].pipe_idx = i;
		dc->hwss.disable_plane(dc,
			&dc->current_state->res_ctx.pipe_ctx[i]);
	}
}