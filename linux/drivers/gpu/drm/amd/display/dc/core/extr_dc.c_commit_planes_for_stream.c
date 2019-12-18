#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_10__* tg; } ;
struct pipe_ctx {TYPE_4__ stream_res; struct dc_plane_state* plane_state; struct dc_stream_state* stream; scalar_t__ bottom_pipe; int /*<<< orphan*/  prev_odm_pipe; int /*<<< orphan*/  top_pipe; } ;
struct dc_surface_update {scalar_t__ flip_addr; struct dc_plane_state* surface; } ;
struct dc_stream_update {int dummy; } ;
struct dc_stream_status {int /*<<< orphan*/  plane_count; } ;
struct dc_stream_state {int apply_seamless_boot_optimization; } ;
struct TYPE_19__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_8__ res_ctx; } ;
struct TYPE_12__ {int /*<<< orphan*/  addr_update; } ;
struct TYPE_13__ {TYPE_1__ bits; } ;
struct dc_plane_state {int triplebuffer_flips; TYPE_2__ update_flags; int /*<<< orphan*/  flip_immediate; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* pipe_control_lock ) (struct dc*,struct pipe_ctx*,int) ;int /*<<< orphan*/  (* update_plane_addr ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* program_triplebuffer ) (struct dc*,struct pipe_ctx*,int) ;int /*<<< orphan*/  (* set_flip_control_gsl ) (struct pipe_ctx*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* apply_ctx_for_surface ) (struct dc*,struct dc_stream_state*,int /*<<< orphan*/ ,struct dc_state*) ;int /*<<< orphan*/  (* prepare_bandwidth ) (struct dc*,struct dc_state*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  disable_tri_buf; } ;
struct dc {int optimize_seamless_boot; int optimized_required; TYPE_7__* res_pool; TYPE_9__ hwss; TYPE_6__ debug; TYPE_5__* ctx; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_18__ {int pipe_count; } ;
struct TYPE_16__ {int /*<<< orphan*/  dce_environment; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* program_manual_trigger ) (TYPE_10__*) ;} ;
struct TYPE_11__ {TYPE_3__* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  IS_DIAG_DC (int /*<<< orphan*/ ) ; 
 int UPDATE_TYPE_FAST ; 
 int UPDATE_TYPE_FULL ; 
 int /*<<< orphan*/  commit_planes_do_stream_update (struct dc*,struct dc_stream_state*,struct dc_stream_update*,int,struct dc_state*) ; 
 int /*<<< orphan*/  context_clock_trace (struct dc*,struct dc_state*) ; 
 struct dc_stream_status* stream_get_status (struct dc_state*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  stub10 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,struct dc_stream_state*,int /*<<< orphan*/ ,struct dc_state*) ; 
 int /*<<< orphan*/  stub3 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub4 (struct dc*,struct dc_stream_state*,int /*<<< orphan*/ ,struct dc_state*) ; 
 int /*<<< orphan*/  stub5 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub6 (struct pipe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub8 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub9 (struct dc*,struct pipe_ctx*,int) ; 

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

	if (dc->optimize_seamless_boot && surface_count > 0) {
		/* Optimize seamless boot flag keeps clocks and watermarks high until
		 * first flip. After first flip, optimization is required to lower
		 * bandwidth. Important to note that it is expected UEFI will
		 * only light up a single display on POST, therefore we only expect
		 * one stream with seamless boot flag set.
		 */
		if (stream->apply_seamless_boot_optimization) {
			stream->apply_seamless_boot_optimization = false;
			dc->optimize_seamless_boot = false;
			dc->optimized_required = true;
		}
	}

	if (update_type == UPDATE_TYPE_FULL && !dc->optimize_seamless_boot) {
		dc->hwss.prepare_bandwidth(dc, context);
		context_clock_trace(dc, context);
	}

	// Stream updates
	if (stream_update)
		commit_planes_do_stream_update(dc, stream, stream_update, update_type, context);

	if (surface_count == 0) {
		/*
		 * In case of turning off screen, no need to program front end a second time.
		 * just return after program blank.
		 */
		dc->hwss.apply_ctx_for_surface(dc, stream, 0, context);
		return;
	}

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	if (!IS_DIAG_DC(dc->ctx->dce_environment)) {
		for (i = 0; i < surface_count; i++) {
			struct dc_plane_state *plane_state = srf_updates[i].surface;
			/*set logical flag for lock/unlock use*/
			for (j = 0; j < dc->res_pool->pipe_count; j++) {
				struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];
				if (!pipe_ctx->plane_state)
					continue;
				if (pipe_ctx->plane_state != plane_state)
					continue;
				plane_state->triplebuffer_flips = false;
				if (update_type == UPDATE_TYPE_FAST &&
					dc->hwss.program_triplebuffer != NULL &&
					!plane_state->flip_immediate &&
					!dc->debug.disable_tri_buf) {
						/*triple buffer for VUpdate  only*/
						plane_state->triplebuffer_flips = true;
				}
			}
		}
	}
#endif

	// Update Type FULL, Surface updates
	for (j = 0; j < dc->res_pool->pipe_count; j++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		if (!pipe_ctx->top_pipe &&
			!pipe_ctx->prev_odm_pipe &&
			pipe_ctx->stream &&
			pipe_ctx->stream == stream) {
			struct dc_stream_status *stream_status = NULL;

			top_pipe_to_program = pipe_ctx;

			if (!pipe_ctx->plane_state)
				continue;

			/* Full fe update*/
			if (update_type == UPDATE_TYPE_FAST)
				continue;

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
			ASSERT(!pipe_ctx->plane_state->triplebuffer_flips);

			if (dc->hwss.program_triplebuffer != NULL &&
				!dc->debug.disable_tri_buf) {
				/*turn off triple buffer for full update*/
				dc->hwss.program_triplebuffer(
					dc, pipe_ctx, pipe_ctx->plane_state->triplebuffer_flips);
			}
#endif
			stream_status =
				stream_get_status(context, pipe_ctx->stream);

			dc->hwss.apply_ctx_for_surface(
					dc, pipe_ctx->stream, stream_status->plane_count, context);
		}
	}

	// Update Type FAST, Surface updates
	if (update_type == UPDATE_TYPE_FAST) {
		/* Lock the top pipe while updating plane addrs, since freesync requires
		 *  plane addr update event triggers to be synchronized.
		 *  top_pipe_to_program is expected to never be NULL
		 */
		dc->hwss.pipe_control_lock(dc, top_pipe_to_program, true);

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
		if (dc->hwss.set_flip_control_gsl)
			for (i = 0; i < surface_count; i++) {
				struct dc_plane_state *plane_state = srf_updates[i].surface;

				for (j = 0; j < dc->res_pool->pipe_count; j++) {
					struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

					if (pipe_ctx->stream != stream)
						continue;

					if (pipe_ctx->plane_state != plane_state)
						continue;

					// GSL has to be used for flip immediate
					dc->hwss.set_flip_control_gsl(pipe_ctx,
							plane_state->flip_immediate);
				}
			}
#endif
		/* Perform requested Updates */
		for (i = 0; i < surface_count; i++) {
			struct dc_plane_state *plane_state = srf_updates[i].surface;

			for (j = 0; j < dc->res_pool->pipe_count; j++) {
				struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

				if (pipe_ctx->stream != stream)
					continue;

				if (pipe_ctx->plane_state != plane_state)
					continue;
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
				/*program triple buffer after lock based on flip type*/
				if (dc->hwss.program_triplebuffer != NULL &&
					!dc->debug.disable_tri_buf) {
					/*only enable triplebuffer for  fast_update*/
					dc->hwss.program_triplebuffer(
						dc, pipe_ctx, plane_state->triplebuffer_flips);
				}
#endif
				if (srf_updates[i].flip_addr)
					dc->hwss.update_plane_addr(dc, pipe_ctx);
			}
		}

		dc->hwss.pipe_control_lock(dc, top_pipe_to_program, false);
	}

	// Fire manual trigger only when bottom plane is flipped
	for (j = 0; j < dc->res_pool->pipe_count; j++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		if (pipe_ctx->bottom_pipe ||
				!pipe_ctx->stream ||
				pipe_ctx->stream != stream ||
				!pipe_ctx->plane_state->update_flags.bits.addr_update)
			continue;

		if (pipe_ctx->stream_res.tg->funcs->program_manual_trigger)
			pipe_ctx->stream_res.tg->funcs->program_manual_trigger(pipe_ctx->stream_res.tg);
	}
}