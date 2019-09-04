#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_6__* tg; TYPE_7__* abm; } ;
struct pipe_ctx {struct dc_stream_state* stream; struct dc_plane_state* plane_state; TYPE_3__ stream_res; int /*<<< orphan*/  top_pipe; } ;
struct dc_surface_update {scalar_t__ flip_addr; struct dc_plane_state* surface; } ;
struct dc_stream_update {scalar_t__ hdr_static_metadata; scalar_t__ periodic_fn_vsync_delta; scalar_t__ abm_level; } ;
struct dc_stream_status {int plane_count; } ;
struct dc_stream_state {int /*<<< orphan*/  periodic_fn_vsync_delta; int /*<<< orphan*/  timing; int /*<<< orphan*/  abm_level; } ;
struct TYPE_11__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_10__ res_ctx; } ;
struct dc_plane_state {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* update_info_frame ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* pipe_control_lock ) (struct dc*,struct pipe_ctx*,int) ;int /*<<< orphan*/  (* update_plane_addr ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* apply_ctx_for_surface ) (struct dc*,struct dc_stream_state*,int,struct dc_state*) ;int /*<<< orphan*/  (* set_bandwidth ) (struct dc*,struct dc_state*,int) ;} ;
struct dc {TYPE_5__ hwss; TYPE_4__* res_pool; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_18__ {TYPE_1__* funcs; } ;
struct TYPE_17__ {TYPE_2__* funcs; } ;
struct TYPE_15__ {int pipe_count; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* program_vline_interrupt ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* is_blanked ) (TYPE_6__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_abm_level ) (TYPE_7__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int UPDATE_TYPE_FAST ; 
 int UPDATE_TYPE_FULL ; 
 int /*<<< orphan*/  context_clock_trace (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  context_timing_trace (struct dc*,TYPE_10__*) ; 
 int /*<<< orphan*/  resource_build_info_frame (struct pipe_ctx*) ; 
 struct dc_stream_status* stream_get_status (struct dc_state*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct dc_state*,int) ; 
 int /*<<< orphan*/  stub10 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub11 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,struct dc_stream_state*,int,struct dc_state*) ; 
 int /*<<< orphan*/  stub3 (struct dc*,struct dc_stream_state*,int,struct dc_state*) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub9 (struct dc*,struct pipe_ctx*) ; 

__attribute__((used)) static void commit_planes_for_stream(struct dc *dc,
		struct dc_surface_update *srf_updates,
		int surface_count,
		struct dc_stream_state *stream,
		struct dc_stream_update *stream_update,
		enum surface_update_type update_type,
		struct dc_state *context)
{
	int i, j;
	struct pipe_ctx *top_pipe_to_program = NULL;

	if (update_type == UPDATE_TYPE_FULL) {
		dc->hwss.set_bandwidth(dc, context, false);
		context_clock_trace(dc, context);
	}

	if (surface_count == 0) {
		/*
		 * In case of turning off screen, no need to program front end a second time.
		 * just return after program front end.
		 */
		dc->hwss.apply_ctx_for_surface(dc, stream, surface_count, context);
		return;
	}

	/* Full fe update*/
	for (j = 0; j < dc->res_pool->pipe_count; j++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		if (!pipe_ctx->top_pipe &&
			pipe_ctx->stream &&
			pipe_ctx->stream == stream) {
			struct dc_stream_status *stream_status = NULL;

			top_pipe_to_program = pipe_ctx;

			if (update_type == UPDATE_TYPE_FAST || !pipe_ctx->plane_state)
				continue;

			stream_status =
					stream_get_status(context, pipe_ctx->stream);

			dc->hwss.apply_ctx_for_surface(
					dc, pipe_ctx->stream, stream_status->plane_count, context);

			if (stream_update && stream_update->abm_level && pipe_ctx->stream_res.abm) {
				if (pipe_ctx->stream_res.tg->funcs->is_blanked) {
					// if otg funcs defined check if blanked before programming
					if (!pipe_ctx->stream_res.tg->funcs->is_blanked(pipe_ctx->stream_res.tg))
						pipe_ctx->stream_res.abm->funcs->set_abm_level(
								pipe_ctx->stream_res.abm, stream->abm_level);
				} else
					pipe_ctx->stream_res.abm->funcs->set_abm_level(
							pipe_ctx->stream_res.abm, stream->abm_level);
			}

			if (stream_update && stream_update->periodic_fn_vsync_delta &&
					pipe_ctx->stream_res.tg->funcs->program_vline_interrupt)
				pipe_ctx->stream_res.tg->funcs->program_vline_interrupt(
						pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing,
						pipe_ctx->stream->periodic_fn_vsync_delta);
		}
	}

	if (update_type == UPDATE_TYPE_FULL)
		context_timing_trace(dc, &context->res_ctx);

	/* Lock the top pipe while updating plane addrs, since freesync requires
	 *  plane addr update event triggers to be synchronized.
	 *  top_pipe_to_program is expected to never be NULL
	 */
	if (update_type == UPDATE_TYPE_FAST) {
		dc->hwss.pipe_control_lock(dc, top_pipe_to_program, true);

		/* Perform requested Updates */
		for (i = 0; i < surface_count; i++) {
			struct dc_plane_state *plane_state = srf_updates[i].surface;

			for (j = 0; j < dc->res_pool->pipe_count; j++) {
				struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

				if (pipe_ctx->stream != stream)
					continue;

				if (pipe_ctx->plane_state != plane_state)
					continue;

				if (srf_updates[i].flip_addr)
					dc->hwss.update_plane_addr(dc, pipe_ctx);
			}
		}

		dc->hwss.pipe_control_lock(dc, top_pipe_to_program, false);
	}

	if (stream && stream_update && update_type > UPDATE_TYPE_FAST)
		for (j = 0; j < dc->res_pool->pipe_count; j++) {
			struct pipe_ctx *pipe_ctx =
					&context->res_ctx.pipe_ctx[j];

			if (pipe_ctx->stream != stream)
				continue;

			if (stream_update->hdr_static_metadata) {
				resource_build_info_frame(pipe_ctx);
				dc->hwss.update_info_frame(pipe_ctx);
			}
		}
}