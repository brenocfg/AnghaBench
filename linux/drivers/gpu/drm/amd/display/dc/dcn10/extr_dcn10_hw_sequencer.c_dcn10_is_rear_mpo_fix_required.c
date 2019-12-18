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
struct pipe_ctx {TYPE_1__* plane_state; struct pipe_ctx* top_pipe; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_2__ {scalar_t__ layer_index; } ;

/* Variables and functions */
 scalar_t__ is_rgb_cspace (int) ; 

__attribute__((used)) static bool dcn10_is_rear_mpo_fix_required(struct pipe_ctx *pipe_ctx, enum dc_color_space colorspace)
{
	if (pipe_ctx->plane_state && pipe_ctx->plane_state->layer_index > 0 && is_rgb_cspace(colorspace)) {
		if (pipe_ctx->top_pipe) {
			struct pipe_ctx *top = pipe_ctx->top_pipe;

			while (top->top_pipe)
				top = top->top_pipe; // Traverse to top pipe_ctx
			if (top->plane_state && top->plane_state->layer_index == 0)
				return true; // Front MPO plane not hidden
		}
	}
	return false;
}