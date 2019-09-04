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
struct pipe_ctx {struct dc_plane_state const* plane_state; } ;
struct TYPE_2__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_1__ res_ctx; } ;
struct dc_plane_state {int dummy; } ;

/* Variables and functions */
 int MAX_PIPES ; 

__attribute__((used)) static bool is_surface_in_context(
		const struct dc_state *context,
		const struct dc_plane_state *plane_state)
{
	int j;

	for (j = 0; j < MAX_PIPES; j++) {
		const struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		if (plane_state == pipe_ctx->plane_state) {
			return true;
		}
	}

	return false;
}