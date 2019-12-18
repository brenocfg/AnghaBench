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
struct TYPE_11__ {struct hubp* hubp; } ;
struct pipe_ctx {TYPE_5__ plane_res; } ;
struct hubp {TYPE_6__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  recovery_enabled; } ;
struct dc {TYPE_4__* current_state; TYPE_2__* res_pool; TYPE_1__ debug; } ;
struct TYPE_12__ {scalar_t__ (* hubp_get_underflow_status ) (struct hubp*) ;int /*<<< orphan*/  (* set_hubp_blank_en ) (struct hubp*,int) ;int /*<<< orphan*/  (* hubp_disable_control ) (struct hubp*,int) ;} ;
struct TYPE_9__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_10__ {TYPE_3__ res_ctx; } ;
struct TYPE_8__ {unsigned int pipe_count; int /*<<< orphan*/  hubbub; } ;

/* Variables and functions */
 int /*<<< orphan*/  hubbub1_soft_reset (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct hubp*) ; 
 int /*<<< orphan*/  stub2 (struct hubp*,int) ; 
 int /*<<< orphan*/  stub3 (struct hubp*,int) ; 
 int /*<<< orphan*/  stub4 (struct hubp*,int) ; 
 int /*<<< orphan*/  stub5 (struct hubp*,int) ; 

__attribute__((used)) static bool dcn10_hw_wa_force_recovery(struct dc *dc)
{
	struct hubp *hubp ;
	unsigned int i;
	bool need_recover = true;

	if (!dc->debug.recovery_enabled)
		return false;

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		if (pipe_ctx != NULL) {
			hubp = pipe_ctx->plane_res.hubp;
			if (hubp != NULL && hubp->funcs->hubp_get_underflow_status) {
				if (hubp->funcs->hubp_get_underflow_status(hubp) != 0) {
					/* one pipe underflow, we will reset all the pipes*/
					need_recover = true;
				}
			}
		}
	}
	if (!need_recover)
		return false;
	/*
	DCHUBP_CNTL:HUBP_BLANK_EN=1
	DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=1
	DCHUBP_CNTL:HUBP_DISABLE=1
	DCHUBP_CNTL:HUBP_DISABLE=0
	DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=0
	DCSURF_PRIMARY_SURFACE_ADDRESS
	DCHUBP_CNTL:HUBP_BLANK_EN=0
	*/

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		if (pipe_ctx != NULL) {
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_BLANK_EN=1*/
			if (hubp != NULL && hubp->funcs->set_hubp_blank_en)
				hubp->funcs->set_hubp_blank_en(hubp, true);
		}
	}
	/*DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=1*/
	hubbub1_soft_reset(dc->res_pool->hubbub, true);

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		if (pipe_ctx != NULL) {
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_DISABLE=1*/
			if (hubp != NULL && hubp->funcs->hubp_disable_control)
				hubp->funcs->hubp_disable_control(hubp, true);
		}
	}
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		if (pipe_ctx != NULL) {
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_DISABLE=0*/
			if (hubp != NULL && hubp->funcs->hubp_disable_control)
				hubp->funcs->hubp_disable_control(hubp, true);
		}
	}
	/*DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=0*/
	hubbub1_soft_reset(dc->res_pool->hubbub, false);
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		if (pipe_ctx != NULL) {
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_BLANK_EN=0*/
			if (hubp != NULL && hubp->funcs->set_hubp_blank_en)
				hubp->funcs->set_hubp_blank_en(hubp, true);
		}
	}
	return true;

}