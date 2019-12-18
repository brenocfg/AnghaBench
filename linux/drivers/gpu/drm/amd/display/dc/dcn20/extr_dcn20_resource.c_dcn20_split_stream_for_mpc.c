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
struct resource_pool {TYPE_2__** dpps; int /*<<< orphan*/ * transforms; int /*<<< orphan*/ * ipps; int /*<<< orphan*/ * hubps; int /*<<< orphan*/ * mis; } ;
struct resource_context {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dsc; } ;
struct TYPE_4__ {int /*<<< orphan*/  mpcc_inst; TYPE_2__* dpp; int /*<<< orphan*/  xfm; int /*<<< orphan*/  ipp; int /*<<< orphan*/  hubp; int /*<<< orphan*/  mi; } ;
struct pipe_ctx {int pipe_idx; int plane_state; struct pipe_ctx* top_pipe; struct pipe_ctx* bottom_pipe; TYPE_3__ stream_res; TYPE_1__ plane_res; } ;
struct TYPE_5__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  resource_build_scaling_params (struct pipe_ctx*) ; 

__attribute__((used)) static void dcn20_split_stream_for_mpc(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		struct pipe_ctx *primary_pipe,
		struct pipe_ctx *secondary_pipe)
{
	int pipe_idx = secondary_pipe->pipe_idx;
	struct pipe_ctx *sec_bot_pipe = secondary_pipe->bottom_pipe;

	*secondary_pipe = *primary_pipe;
	secondary_pipe->bottom_pipe = sec_bot_pipe;

	secondary_pipe->pipe_idx = pipe_idx;
	secondary_pipe->plane_res.mi = pool->mis[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.hubp = pool->hubps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.ipp = pool->ipps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.xfm = pool->transforms[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.dpp = pool->dpps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.mpcc_inst = pool->dpps[secondary_pipe->pipe_idx]->inst;
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	secondary_pipe->stream_res.dsc = NULL;
#endif
	if (primary_pipe->bottom_pipe && primary_pipe->bottom_pipe != secondary_pipe) {
		ASSERT(!secondary_pipe->bottom_pipe);
		secondary_pipe->bottom_pipe = primary_pipe->bottom_pipe;
		secondary_pipe->bottom_pipe->top_pipe = secondary_pipe;
	}
	primary_pipe->bottom_pipe = secondary_pipe;
	secondary_pipe->top_pipe = primary_pipe;

	ASSERT(primary_pipe->plane_state);
	resource_build_scaling_params(primary_pipe);
	resource_build_scaling_params(secondary_pipe);
}