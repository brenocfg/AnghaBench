#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct pwl_params {int dummy; } ;
struct TYPE_20__ {TYPE_6__* opp; } ;
struct TYPE_15__ {TYPE_1__* hubp; } ;
struct pipe_ctx {TYPE_9__* stream; int /*<<< orphan*/ * top_pipe; TYPE_7__ stream_res; TYPE_2__ plane_res; } ;
struct mpc {TYPE_10__* funcs; struct pwl_params blender_params; } ;
struct dc_stream_state {TYPE_11__* out_transfer_func; } ;
struct TYPE_22__ {TYPE_8__* out_transfer_func; } ;
struct TYPE_21__ {scalar_t__ type; } ;
struct TYPE_19__ {TYPE_5__* ctx; } ;
struct TYPE_18__ {TYPE_4__* dc; } ;
struct TYPE_17__ {TYPE_3__* res_pool; } ;
struct TYPE_16__ {struct mpc* mpc; } ;
struct TYPE_14__ {int inst; } ;
struct TYPE_13__ {scalar_t__ type; struct pwl_params pwl; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_output_gamma ) (struct mpc*,int,struct pwl_params*) ;int /*<<< orphan*/  (* power_on_mpc_mem_pwr ) (struct mpc*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 scalar_t__ TF_TYPE_DISTRIBUTED_POINTS ; 
 scalar_t__ TF_TYPE_HWPWL ; 
 scalar_t__ TF_TYPE_PREDEFINED ; 
 scalar_t__ cm_helper_translate_curve_to_hw_format (TYPE_11__*,struct pwl_params*,int) ; 
 int /*<<< orphan*/  stub1 (struct mpc*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mpc*,int,struct pwl_params*) ; 

bool dcn20_set_output_transfer_func(struct pipe_ctx *pipe_ctx,
				const struct dc_stream_state *stream)
{
	int mpcc_id = pipe_ctx->plane_res.hubp->inst;
	struct mpc *mpc = pipe_ctx->stream_res.opp->ctx->dc->res_pool->mpc;
	struct pwl_params *params = NULL;
	/*
	 * program OGAM only for the top pipe
	 * if there is a pipe split then fix diagnostic is required:
	 * how to pass OGAM parameter for stream.
	 * if programming for all pipes is required then remove condition
	 * pipe_ctx->top_pipe == NULL ,but then fix the diagnostic.
	 */
	if (mpc->funcs->power_on_mpc_mem_pwr)
		mpc->funcs->power_on_mpc_mem_pwr(mpc, mpcc_id, true);
	if (pipe_ctx->top_pipe == NULL
			&& mpc->funcs->set_output_gamma && stream->out_transfer_func) {
		if (stream->out_transfer_func->type == TF_TYPE_HWPWL)
			params = &stream->out_transfer_func->pwl;
		else if (pipe_ctx->stream->out_transfer_func->type ==
			TF_TYPE_DISTRIBUTED_POINTS &&
			cm_helper_translate_curve_to_hw_format(
			stream->out_transfer_func,
			&mpc->blender_params, false))
			params = &mpc->blender_params;
		/*
		 * there is no ROM
		 */
		if (stream->out_transfer_func->type == TF_TYPE_PREDEFINED)
			BREAK_TO_DEBUGGER();
	}
	/*
	 * if above if is not executed then 'params' equal to 0 and set in bypass
	 */
	mpc->funcs->set_output_gamma(mpc, mpcc_id, params);

	return true;
}