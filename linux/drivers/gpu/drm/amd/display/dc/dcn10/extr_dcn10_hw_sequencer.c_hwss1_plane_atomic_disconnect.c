#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t mpcc_inst; TYPE_1__* dpp; struct hubp* hubp; } ;
struct TYPE_10__ {struct output_pixel_processor* opp; } ;
struct pipe_ctx {TYPE_5__ plane_res; TYPE_3__ stream_res; } ;
struct mpc_tree {int dummy; } ;
struct output_pixel_processor {int* mpcc_disconnect_pending; struct mpc_tree mpc_tree_params; } ;
struct mpcc {int dummy; } ;
struct mpc {TYPE_4__* funcs; } ;
struct hubp {TYPE_6__* funcs; } ;
struct TYPE_14__ {scalar_t__ sanity_checks; } ;
struct dc {int optimized_required; TYPE_7__ debug; TYPE_2__* res_pool; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* hubp_disconnect ) (struct hubp*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* remove_mpcc ) (struct mpc*,struct mpc_tree*,struct mpcc*) ;struct mpcc* (* get_mpcc_for_dpp ) (struct mpc_tree*,int) ;} ;
struct TYPE_9__ {struct mpc* mpc; } ;
struct TYPE_8__ {int inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_verify_allow_pstate_change_high (struct dc*) ; 
 struct mpcc* stub1 (struct mpc_tree*,int) ; 
 int /*<<< orphan*/  stub2 (struct mpc*,struct mpc_tree*,struct mpcc*) ; 
 int /*<<< orphan*/  stub3 (struct hubp*) ; 

void hwss1_plane_atomic_disconnect(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	struct hubp *hubp = pipe_ctx->plane_res.hubp;
	int dpp_id = pipe_ctx->plane_res.dpp->inst;
	struct mpc *mpc = dc->res_pool->mpc;
	struct mpc_tree *mpc_tree_params;
	struct mpcc *mpcc_to_remove = NULL;
	struct output_pixel_processor *opp = pipe_ctx->stream_res.opp;

	mpc_tree_params = &(opp->mpc_tree_params);
	mpcc_to_remove = mpc->funcs->get_mpcc_for_dpp(mpc_tree_params, dpp_id);

	/*Already reset*/
	if (mpcc_to_remove == NULL)
		return;

	mpc->funcs->remove_mpcc(mpc, mpc_tree_params, mpcc_to_remove);
	if (opp != NULL)
		opp->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;

	dc->optimized_required = true;

	if (hubp->funcs->hubp_disconnect)
		hubp->funcs->hubp_disconnect(hubp);

	if (dc->debug.sanity_checks)
		dcn10_verify_allow_pstate_change_high(dc);
}