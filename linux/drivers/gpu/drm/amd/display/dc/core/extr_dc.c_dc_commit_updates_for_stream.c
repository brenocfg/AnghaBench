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
struct pipe_ctx {TYPE_3__* plane_state; struct dc_stream_state* stream; } ;
struct dc_surface_update {struct dc_plane_state* surface; } ;
struct dc_stream_update {int dummy; } ;
struct dc_stream_status {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_5__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_2__ res_ctx; } ;
struct dc_plane_state {int dummy; } ;
struct dc_context {int dummy; } ;
struct dc {TYPE_1__* res_pool; struct dc_state* current_state; struct dc_context* ctx; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_6__ {int force_full_update; } ;
struct TYPE_4__ {int pipe_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERROR (char*) ; 
 int UPDATE_TYPE_FULL ; 
 int /*<<< orphan*/  commit_planes_for_stream (struct dc*,struct dc_surface_update*,int,struct dc_stream_state*,struct dc_stream_update*,int,struct dc_state*) ; 
 int /*<<< orphan*/  copy_stream_update_to_stream (struct dc*,struct dc_state*,struct dc_stream_state*,struct dc_stream_update*) ; 
 int /*<<< orphan*/  copy_surface_update_to_plane (struct dc_plane_state*,struct dc_surface_update*) ; 
 int dc_check_update_surfaces_for_stream (struct dc*,struct dc_surface_update*,int,struct dc_stream_update*,struct dc_stream_status const*) ; 
 struct dc_state* dc_create_state (struct dc*) ; 
 int /*<<< orphan*/  dc_post_update_surfaces_to_stream (struct dc*) ; 
 int /*<<< orphan*/  dc_release_state (struct dc_state*) ; 
 int /*<<< orphan*/  dc_resource_state_copy_construct (struct dc_state*,struct dc_state*) ; 
 struct dc_stream_status* dc_stream_get_status (struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_surface_trace (struct dc*,struct dc_surface_update*,int) ; 
 int update_surface_trace_level ; 

void dc_commit_updates_for_stream(struct dc *dc,
		struct dc_surface_update *srf_updates,
		int surface_count,
		struct dc_stream_state *stream,
		struct dc_stream_update *stream_update,
		struct dc_state *state)
{
	const struct dc_stream_status *stream_status;
	enum surface_update_type update_type;
	struct dc_state *context;
	struct dc_context *dc_ctx = dc->ctx;
	int i;

	stream_status = dc_stream_get_status(stream);
	context = dc->current_state;

	update_type = dc_check_update_surfaces_for_stream(
				dc, srf_updates, surface_count, stream_update, stream_status);

	if (update_type >= update_surface_trace_level)
		update_surface_trace(dc, srf_updates, surface_count);


	if (update_type >= UPDATE_TYPE_FULL) {

		/* initialize scratch memory for building context */
		context = dc_create_state(dc);
		if (context == NULL) {
			DC_ERROR("Failed to allocate new validate context!\n");
			return;
		}

		dc_resource_state_copy_construct(state, context);

		for (i = 0; i < dc->res_pool->pipe_count; i++) {
			struct pipe_ctx *new_pipe = &context->res_ctx.pipe_ctx[i];
			struct pipe_ctx *old_pipe = &dc->current_state->res_ctx.pipe_ctx[i];

			if (new_pipe->plane_state && new_pipe->plane_state != old_pipe->plane_state)
				new_pipe->plane_state->force_full_update = true;
		}
	}


	for (i = 0; i < surface_count; i++) {
		struct dc_plane_state *surface = srf_updates[i].surface;

		copy_surface_update_to_plane(surface, &srf_updates[i]);

	}

	copy_stream_update_to_stream(dc, context, stream, stream_update);

	commit_planes_for_stream(
				dc,
				srf_updates,
				surface_count,
				stream,
				stream_update,
				update_type,
				context);
	/*update current_State*/
	if (dc->current_state != context) {

		struct dc_state *old = dc->current_state;

		dc->current_state = context;
		dc_release_state(old);

		for (i = 0; i < dc->res_pool->pipe_count; i++) {
			struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

			if (pipe_ctx->plane_state && pipe_ctx->stream == stream)
				pipe_ctx->plane_state->force_full_update = false;
		}
	}
	/*let's use current_state to update watermark etc*/
	if (update_type >= UPDATE_TYPE_FULL)
		dc_post_update_surfaces_to_stream(dc);

	return;

}