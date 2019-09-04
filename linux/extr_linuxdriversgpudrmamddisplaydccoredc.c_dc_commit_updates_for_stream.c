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
struct pipe_ctx {struct dc_plane_state* plane_state; } ;
struct dc_surface_update {TYPE_1__* flip_addr; struct dc_plane_state* surface; } ;
struct dc_stream_update {int dummy; } ;
struct dc_stream_status {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_6__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_3__ res_ctx; } ;
struct dc_plane_state {int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; } ;
struct dc_context {int dummy; } ;
struct dc {struct dc_state* current_state; TYPE_2__* res_pool; struct dc_context* ctx; } ;
typedef  enum surface_update_type { ____Placeholder_surface_update_type } surface_update_type ;
struct TYPE_5__ {int pipe_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  flip_immediate; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERROR (char*) ; 
 int UPDATE_TYPE_FULL ; 
 int UPDATE_TYPE_MED ; 
 int /*<<< orphan*/  commit_planes_for_stream (struct dc*,struct dc_surface_update*,int,struct dc_stream_state*,struct dc_stream_update*,int,struct dc_state*) ; 
 int dc_check_update_surfaces_for_stream (struct dc*,struct dc_surface_update*,int,struct dc_stream_update*,struct dc_stream_status const*) ; 
 struct dc_state* dc_create_state () ; 
 int /*<<< orphan*/  dc_post_update_surfaces_to_stream (struct dc*) ; 
 int /*<<< orphan*/  dc_release_state (struct dc_state*) ; 
 int /*<<< orphan*/  dc_resource_state_copy_construct (struct dc_state*,struct dc_state*) ; 
 struct dc_stream_status* dc_stream_get_status (struct dc_stream_state*) ; 
 int /*<<< orphan*/  resource_build_scaling_params (struct pipe_ctx*) ; 
 int /*<<< orphan*/  update_surface_trace (struct dc*,struct dc_surface_update*,int) ; 
 int update_surface_trace_level ; 

void dc_commit_updates_for_stream(struct dc *dc,
		struct dc_surface_update *srf_updates,
		int surface_count,
		struct dc_stream_state *stream,
		struct dc_stream_update *stream_update,
		struct dc_plane_state **plane_states,
		struct dc_state *state)
{
	const struct dc_stream_status *stream_status;
	enum surface_update_type update_type;
	struct dc_state *context;
	struct dc_context *dc_ctx = dc->ctx;
	int i, j;

	stream_status = dc_stream_get_status(stream);
	context = dc->current_state;

	update_type = dc_check_update_surfaces_for_stream(
				dc, srf_updates, surface_count, stream_update, stream_status);

	if (update_type >= update_surface_trace_level)
		update_surface_trace(dc, srf_updates, surface_count);


	if (update_type >= UPDATE_TYPE_FULL) {

		/* initialize scratch memory for building context */
		context = dc_create_state();
		if (context == NULL) {
			DC_ERROR("Failed to allocate new validate context!\n");
			return;
		}

		dc_resource_state_copy_construct(state, context);
	}


	for (i = 0; i < surface_count; i++) {
		struct dc_plane_state *surface = srf_updates[i].surface;

		/* TODO: On flip we don't build the state, so it still has the
		 * old address. Which is why we are updating the address here
		 */
		if (srf_updates[i].flip_addr) {
			surface->address = srf_updates[i].flip_addr->address;
			surface->flip_immediate = srf_updates[i].flip_addr->flip_immediate;

		}

		if (update_type >= UPDATE_TYPE_MED) {
			for (j = 0; j < dc->res_pool->pipe_count; j++) {
				struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

				if (pipe_ctx->plane_state != surface)
					continue;

				resource_build_scaling_params(pipe_ctx);
			}
		}
	}

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

	}
	/*let's use current_state to update watermark etc*/
	if (update_type >= UPDATE_TYPE_FULL)
		dc_post_update_surfaces_to_stream(dc);

	return;

}