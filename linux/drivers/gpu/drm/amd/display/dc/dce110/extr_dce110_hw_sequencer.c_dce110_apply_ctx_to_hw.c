#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct pipe_ctx {scalar_t__ clock_source; scalar_t__ prev_odm_pipe; scalar_t__ top_pipe; TYPE_8__* stream; } ;
struct TYPE_19__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {scalar_t__ stream_count; TYPE_6__ res_ctx; } ;
struct dc_bios {TYPE_9__* funcs; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* enable_display_power_gating ) (struct dc*,int,struct dc_bios*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reset_hw_ctx_wrap ) (struct dc*,struct dc_state*) ;} ;
struct dc {TYPE_11__* current_state; TYPE_10__* fbc_compressor; TYPE_4__* res_pool; TYPE_2__* ctx; TYPE_1__ hwss; int /*<<< orphan*/  hwseq; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_22__ {int /*<<< orphan*/  (* set_scratch_critical_state ) (struct dc_bios*,int) ;} ;
struct TYPE_21__ {TYPE_7__* link; } ;
struct TYPE_20__ {scalar_t__ link_state_valid; } ;
struct TYPE_18__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_17__ {int pipe_count; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* disable_fbc ) (TYPE_10__*) ;} ;
struct TYPE_15__ {struct dc_bios* dc_bios; } ;
struct TYPE_13__ {TYPE_5__ res_ctx; } ;
struct TYPE_12__ {TYPE_3__* funcs; } ;

/* Variables and functions */
 int DC_OK ; 
 int /*<<< orphan*/  PIPE_GATING_CONTROL_DISABLE ; 
 int apply_single_controller_ctx_to_hw (struct pipe_ctx*,struct dc_state*,struct dc*) ; 
 int /*<<< orphan*/  dce110_setup_audio_dto (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  dce_crtc_switch_to_clk_src (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  enable_fbc (struct dc*,TYPE_11__*) ; 
 int /*<<< orphan*/  pipe_need_reprogram (struct pipe_ctx*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  stub2 (struct dc_bios*,int) ; 
 int /*<<< orphan*/  stub3 (struct dc*,int,struct dc_bios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub5 (struct dc_bios*,int) ; 

enum dc_status dce110_apply_ctx_to_hw(
		struct dc *dc,
		struct dc_state *context)
{
	struct dc_bios *dcb = dc->ctx->dc_bios;
	enum dc_status status;
	int i;

	/* Reset old context */
	/* look up the targets that have been removed since last commit */
	dc->hwss.reset_hw_ctx_wrap(dc, context);

	/* Skip applying if no targets */
	if (context->stream_count <= 0)
		return DC_OK;

	/* Apply new context */
	dcb->funcs->set_scratch_critical_state(dcb, true);

	/* below is for real asic only */
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx_old =
					&dc->current_state->res_ctx.pipe_ctx[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		if (pipe_ctx->stream == NULL || pipe_ctx->top_pipe)
			continue;

		if (pipe_ctx->stream == pipe_ctx_old->stream) {
			if (pipe_ctx_old->clock_source != pipe_ctx->clock_source)
				dce_crtc_switch_to_clk_src(dc->hwseq,
						pipe_ctx->clock_source, i);
			continue;
		}

		dc->hwss.enable_display_power_gating(
				dc, i, dc->ctx->dc_bios,
				PIPE_GATING_CONTROL_DISABLE);
	}

	if (dc->fbc_compressor)
		dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);

	dce110_setup_audio_dto(dc, context);

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx_old =
					&dc->current_state->res_ctx.pipe_ctx[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		if (pipe_ctx->stream == NULL)
			continue;

		if (pipe_ctx->stream == pipe_ctx_old->stream &&
			pipe_ctx->stream->link->link_state_valid) {
			continue;
		}

		if (pipe_ctx_old->stream && !pipe_need_reprogram(pipe_ctx_old, pipe_ctx))
			continue;

		if (pipe_ctx->top_pipe || pipe_ctx->prev_odm_pipe)
			continue;

		status = apply_single_controller_ctx_to_hw(
				pipe_ctx,
				context,
				dc);

		if (DC_OK != status)
			return status;
	}

	if (dc->fbc_compressor)
		enable_fbc(dc, dc->current_state);

	dcb->funcs->set_scratch_critical_state(dcb, false);

	return DC_OK;
}