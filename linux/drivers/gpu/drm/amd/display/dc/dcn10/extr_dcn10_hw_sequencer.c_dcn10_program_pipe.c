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
struct pipe_ctx {int /*<<< orphan*/  stream; TYPE_4__* plane_state; } ;
struct dc_state {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_output_transfer_func ) (struct pipe_ctx*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_input_transfer_func ) (struct pipe_ctx*,TYPE_4__*) ;} ;
struct dc {TYPE_3__ hwss; } ;
struct TYPE_5__ {scalar_t__ full_update; scalar_t__ gamma_change; scalar_t__ in_transfer_func_change; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct TYPE_8__ {TYPE_2__ update_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_enable_plane (struct dc*,struct pipe_ctx*,struct dc_state*) ; 
 int /*<<< orphan*/  set_hdr_multiplier (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_dchubp_dpp (struct dc*,struct pipe_ctx*,struct dc_state*) ; 

void dcn10_program_pipe(
		struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		struct dc_state *context)
{
	if (pipe_ctx->plane_state->update_flags.bits.full_update)
		dcn10_enable_plane(dc, pipe_ctx, context);

	update_dchubp_dpp(dc, pipe_ctx, context);

	set_hdr_multiplier(pipe_ctx);

	if (pipe_ctx->plane_state->update_flags.bits.full_update ||
			pipe_ctx->plane_state->update_flags.bits.in_transfer_func_change ||
			pipe_ctx->plane_state->update_flags.bits.gamma_change)
		dc->hwss.set_input_transfer_func(pipe_ctx, pipe_ctx->plane_state);

	/* dcn10_translate_regamma_to_hw_format takes 750us to finish
	 * only do gamma programming for full update.
	 * TODO: This can be further optimized/cleaned up
	 * Always call this for now since it does memcmp inside before
	 * doing heavy calculation and programming
	 */
	if (pipe_ctx->plane_state->update_flags.bits.full_update)
		dc->hwss.set_output_transfer_func(pipe_ctx, pipe_ctx->stream);
}