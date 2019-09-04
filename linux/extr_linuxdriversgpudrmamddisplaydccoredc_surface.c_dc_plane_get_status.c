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
struct pipe_ctx {struct dc_plane_state const* plane_state; } ;
struct dc_plane_status {int dummy; } ;
struct dc_plane_state {TYPE_1__* ctx; struct dc_plane_status status; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* update_pending_status ) (struct pipe_ctx*) ;} ;
struct dc {TYPE_5__ hwss; TYPE_4__* current_state; TYPE_2__* res_pool; } ;
struct TYPE_8__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_9__ {TYPE_3__ res_ctx; } ;
struct TYPE_7__ {int pipe_count; } ;
struct TYPE_6__ {struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*) ; 

const struct dc_plane_status *dc_plane_get_status(
		const struct dc_plane_state *plane_state)
{
	const struct dc_plane_status *plane_status;
	struct dc  *core_dc;
	int i;

	if (!plane_state ||
		!plane_state->ctx ||
		!plane_state->ctx->dc) {
		ASSERT(0);
		return NULL; /* remove this if above assert never hit */
	}

	plane_status = &plane_state->status;
	core_dc = plane_state->ctx->dc;

	if (core_dc->current_state == NULL)
		return NULL;

	for (i = 0; i < core_dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx =
				&core_dc->current_state->res_ctx.pipe_ctx[i];

		if (pipe_ctx->plane_state != plane_state)
			continue;

		core_dc->hwss.update_pending_status(pipe_ctx);
	}

	return plane_status;
}