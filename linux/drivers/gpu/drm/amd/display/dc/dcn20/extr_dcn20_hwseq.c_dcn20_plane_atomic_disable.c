#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ gsl_group; struct hubp* hubp; struct dpp* dpp; } ;
struct pipe_ctx {int /*<<< orphan*/ * plane_state; int /*<<< orphan*/ * bottom_pipe; int /*<<< orphan*/ * top_pipe; TYPE_4__ plane_res; TYPE_4__ stream_res; int /*<<< orphan*/ * stream; } ;
struct hubp {int power_gated; TYPE_1__* funcs; } ;
struct dpp {TYPE_2__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* plane_atomic_power_down ) (struct dc*,struct dpp*,struct hubp*) ;int /*<<< orphan*/  (* set_flip_control_gsl ) (struct pipe_ctx*,int) ;int /*<<< orphan*/  (* wait_for_mpcc_disconnect ) (struct dc*,int /*<<< orphan*/ ,struct pipe_ctx*) ;} ;
struct dc {int optimized_required; TYPE_3__ hwss; int /*<<< orphan*/  res_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* dpp_dppclk_control ) (struct dpp*,int,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* hubp_clk_cntl ) (struct hubp*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dcn20_setup_gsl_group_as_lock (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc*,int /*<<< orphan*/ ,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub3 (struct hubp*,int) ; 
 int /*<<< orphan*/  stub4 (struct dpp*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct dc*,struct dpp*,struct hubp*) ; 

__attribute__((used)) static void dcn20_plane_atomic_disable(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	struct hubp *hubp = pipe_ctx->plane_res.hubp;
	struct dpp *dpp = pipe_ctx->plane_res.dpp;

	dc->hwss.wait_for_mpcc_disconnect(dc, dc->res_pool, pipe_ctx);

	/* In flip immediate with pipe splitting case GSL is used for
	 * synchronization so we must disable it when the plane is disabled.
	 */
	if (pipe_ctx->stream_res.gsl_group != 0)
		dcn20_setup_gsl_group_as_lock(dc, pipe_ctx, false);

	dc->hwss.set_flip_control_gsl(pipe_ctx, false);

	hubp->funcs->hubp_clk_cntl(hubp, false);

	dpp->funcs->dpp_dppclk_control(dpp, false, false);

	hubp->power_gated = true;
	dc->optimized_required = false; /* We're powering off, no need to optimize */

	dc->hwss.plane_atomic_power_down(dc,
			pipe_ctx->plane_res.dpp,
			pipe_ctx->plane_res.hubp);

	pipe_ctx->stream = NULL;
	memset(&pipe_ctx->stream_res, 0, sizeof(pipe_ctx->stream_res));
	memset(&pipe_ctx->plane_res, 0, sizeof(pipe_ctx->plane_res));
	pipe_ctx->top_pipe = NULL;
	pipe_ctx->bottom_pipe = NULL;
	pipe_ctx->plane_state = NULL;
}