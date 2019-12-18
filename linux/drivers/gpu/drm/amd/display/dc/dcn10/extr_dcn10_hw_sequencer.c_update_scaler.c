#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int alpha_en; int /*<<< orphan*/  depth; } ;
struct TYPE_12__ {TYPE_3__ lb_params; } ;
struct TYPE_10__ {TYPE_6__ scl_data; TYPE_5__* dpp; } ;
struct pipe_ctx {TYPE_4__ plane_res; scalar_t__ bottom_pipe; TYPE_2__* plane_state; } ;
struct TYPE_11__ {TYPE_1__* funcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  per_pixel_alpha; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* dpp_set_scaler ) (TYPE_5__*,TYPE_6__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LB_PIXEL_DEPTH_30BPP ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static void update_scaler(struct pipe_ctx *pipe_ctx)
{
	bool per_pixel_alpha =
			pipe_ctx->plane_state->per_pixel_alpha && pipe_ctx->bottom_pipe;

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = per_pixel_alpha;
	pipe_ctx->plane_res.scl_data.lb_params.depth = LB_PIXEL_DEPTH_30BPP;
	/* scaler configuration */
	pipe_ctx->plane_res.dpp->funcs->dpp_set_scaler(
			pipe_ctx->plane_res.dpp, &pipe_ctx->plane_res.scl_data);
}