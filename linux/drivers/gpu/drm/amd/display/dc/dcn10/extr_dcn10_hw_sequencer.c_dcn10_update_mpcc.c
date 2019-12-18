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
struct TYPE_13__ {TYPE_10__* opp; } ;
struct TYPE_14__ {struct hubp* hubp; } ;
struct pipe_ctx {TYPE_11__ stream_res; TYPE_6__* plane_state; TYPE_3__* stream; scalar_t__ bottom_pipe; TYPE_1__ plane_res; } ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
struct mpcc_blnd_cfg {int overlap_only; int global_gain; int global_alpha; int pre_multiplied_alpha; int /*<<< orphan*/  alpha_mode; int /*<<< orphan*/  black_color; TYPE_2__ member_0; } ;
struct mpcc {int dummy; } ;
struct mpc_tree {int dummy; } ;
struct mpc {TYPE_8__* funcs; } ;
struct hubp {int inst; int mpcc_id; int /*<<< orphan*/  opp_id; } ;
struct TYPE_20__ {scalar_t__ visual_confirm; scalar_t__ sanity_checks; } ;
struct dc {TYPE_9__* res_pool; TYPE_7__ debug; } ;
struct TYPE_22__ {struct mpc* mpc; } ;
struct TYPE_21__ {struct mpcc* (* insert_plane ) (struct mpc*,struct mpc_tree*,struct mpcc_blnd_cfg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ;int /*<<< orphan*/  (* assert_mpcc_idle_before_connect ) (struct mpc*,int) ;int /*<<< orphan*/  (* remove_mpcc ) (struct mpc*,struct mpc_tree*,struct mpcc*) ;struct mpcc* (* get_mpcc_for_dpp ) (struct mpc_tree*,int) ;int /*<<< orphan*/  (* update_blending ) (struct mpc*,struct mpcc_blnd_cfg*,int) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  full_update; } ;
struct TYPE_18__ {TYPE_4__ bits; } ;
struct TYPE_19__ {int global_alpha_value; TYPE_5__ update_flags; scalar_t__ global_alpha; int /*<<< orphan*/  per_pixel_alpha; } ;
struct TYPE_16__ {int /*<<< orphan*/  output_color_space; } ;
struct TYPE_12__ {int /*<<< orphan*/  inst; struct mpc_tree mpc_tree_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPCC_ALPHA_BLEND_MODE_GLOBAL_ALPHA ; 
 int /*<<< orphan*/  MPCC_ALPHA_BLEND_MODE_PER_PIXEL_ALPHA ; 
 scalar_t__ VISUAL_CONFIRM_HDR ; 
 scalar_t__ VISUAL_CONFIRM_SURFACE ; 
 int /*<<< orphan*/  color_space_to_black_color (struct dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcn10_get_hdr_visual_confirm_color (struct pipe_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcn10_get_surface_visual_confirm_color (struct pipe_ctx*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_rgb_cspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mpc*,struct mpcc_blnd_cfg*,int) ; 
 struct mpcc* stub2 (struct mpc_tree*,int) ; 
 int /*<<< orphan*/  stub3 (struct mpc*,struct mpc_tree*,struct mpcc*) ; 
 int /*<<< orphan*/  stub4 (struct mpc*,int) ; 
 struct mpcc* stub5 (struct mpc*,struct mpc_tree*,struct mpcc_blnd_cfg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void dcn10_update_mpcc(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	struct hubp *hubp = pipe_ctx->plane_res.hubp;
	struct mpcc_blnd_cfg blnd_cfg = {{0}};
	bool per_pixel_alpha = pipe_ctx->plane_state->per_pixel_alpha && pipe_ctx->bottom_pipe;
	int mpcc_id;
	struct mpcc *new_mpcc;
	struct mpc *mpc = dc->res_pool->mpc;
	struct mpc_tree *mpc_tree_params = &(pipe_ctx->stream_res.opp->mpc_tree_params);

	if (dc->debug.visual_confirm == VISUAL_CONFIRM_HDR) {
		dcn10_get_hdr_visual_confirm_color(
				pipe_ctx, &blnd_cfg.black_color);
	} else if (dc->debug.visual_confirm == VISUAL_CONFIRM_SURFACE) {
		dcn10_get_surface_visual_confirm_color(
				pipe_ctx, &blnd_cfg.black_color);
	} else {
		color_space_to_black_color(
				dc, pipe_ctx->stream->output_color_space,
				&blnd_cfg.black_color);
	}

	if (per_pixel_alpha)
		blnd_cfg.alpha_mode = MPCC_ALPHA_BLEND_MODE_PER_PIXEL_ALPHA;
	else
		blnd_cfg.alpha_mode = MPCC_ALPHA_BLEND_MODE_GLOBAL_ALPHA;

	blnd_cfg.overlap_only = false;
	blnd_cfg.global_gain = 0xff;

	if (pipe_ctx->plane_state->global_alpha)
		blnd_cfg.global_alpha = pipe_ctx->plane_state->global_alpha_value;
	else
		blnd_cfg.global_alpha = 0xff;

	/* DCN1.0 has output CM before MPC which seems to screw with
	 * pre-multiplied alpha.
	 */
	blnd_cfg.pre_multiplied_alpha = is_rgb_cspace(
			pipe_ctx->stream->output_color_space)
					&& per_pixel_alpha;


	/*
	 * TODO: remove hack
	 * Note: currently there is a bug in init_hw such that
	 * on resume from hibernate, BIOS sets up MPCC0, and
	 * we do mpcc_remove but the mpcc cannot go to idle
	 * after remove. This cause us to pick mpcc1 here,
	 * which causes a pstate hang for yet unknown reason.
	 */
	mpcc_id = hubp->inst;

	/* If there is no full update, don't need to touch MPC tree*/
	if (!pipe_ctx->plane_state->update_flags.bits.full_update) {
		mpc->funcs->update_blending(mpc, &blnd_cfg, mpcc_id);
		return;
	}

	/* check if this MPCC is already being used */
	new_mpcc = mpc->funcs->get_mpcc_for_dpp(mpc_tree_params, mpcc_id);
	/* remove MPCC if being used */
	if (new_mpcc != NULL)
		mpc->funcs->remove_mpcc(mpc, mpc_tree_params, new_mpcc);
	else
		if (dc->debug.sanity_checks)
			mpc->funcs->assert_mpcc_idle_before_connect(
					dc->res_pool->mpc, mpcc_id);

	/* Call MPC to insert new plane */
	new_mpcc = mpc->funcs->insert_plane(dc->res_pool->mpc,
			mpc_tree_params,
			&blnd_cfg,
			NULL,
			NULL,
			hubp->inst,
			mpcc_id);

	ASSERT(new_mpcc != NULL);

	hubp->opp_id = pipe_ctx->stream_res.opp->inst;
	hubp->mpcc_id = mpcc_id;
}