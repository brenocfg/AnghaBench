#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct timing_generator {TYPE_13__* funcs; } ;
struct TYPE_27__ {size_t mpcc_inst; struct hubp* hubp; struct dpp* dpp; } ;
struct TYPE_28__ {struct timing_generator* tg; TYPE_10__* opp; } ;
struct pipe_ctx {int pipe_idx; TYPE_8__ plane_res; TYPE_9__ stream_res; int /*<<< orphan*/ * stream; } ;
struct hubp {size_t mpcc_id; int power_gated; int /*<<< orphan*/  opp_id; } ;
struct dpp {size_t inst; TYPE_6__* funcs; } ;
struct TYPE_22__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_3__ res_ctx; TYPE_1__** streams; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* disable_plane ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* plane_atomic_disconnect ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* init_blank ) (struct dc*,struct timing_generator*) ;} ;
struct dc {TYPE_12__ hwss; TYPE_11__* res_pool; TYPE_5__* current_state; } ;
struct TYPE_26__ {int /*<<< orphan*/ * opp_list; int /*<<< orphan*/  opp_id; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* dpp_reset ) (struct dpp*) ;} ;
struct TYPE_23__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_24__ {TYPE_4__ res_ctx; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* mpc_init_single_inst ) (TYPE_14__*,int) ;} ;
struct TYPE_20__ {scalar_t__ apply_seamless_boot_optimization; } ;
struct TYPE_19__ {TYPE_2__* funcs; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* tg_init ) (struct timing_generator*) ;int /*<<< orphan*/  (* unlock ) (struct timing_generator*) ;scalar_t__ (* is_tg_enabled ) (struct timing_generator*) ;int /*<<< orphan*/  (* set_blank ) (struct timing_generator*,int) ;int /*<<< orphan*/  (* lock ) (struct timing_generator*) ;} ;
struct TYPE_16__ {int pipe_count; TYPE_10__** opps; struct dpp** dpps; struct hubp** hubps; struct timing_generator** timing_generators; TYPE_14__* mpc; } ;
struct TYPE_15__ {int* mpcc_disconnect_pending; TYPE_7__ mpc_tree_params; int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPP_ID_INVALID ; 
 int /*<<< orphan*/  hwss_wait_for_blank_complete (struct timing_generator*) ; 
 scalar_t__ stub1 (struct timing_generator*) ; 
 scalar_t__ stub10 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub11 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub12 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub13 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,struct timing_generator*) ; 
 int /*<<< orphan*/  stub3 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub4 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub5 (struct timing_generator*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_14__*,int) ; 
 scalar_t__ stub7 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub8 (struct dpp*) ; 
 int /*<<< orphan*/  stub9 (struct dc*,struct pipe_ctx*) ; 

__attribute__((used)) static void dcn10_init_pipes(struct dc *dc, struct dc_state *context)
{
	int i;
	bool can_apply_seamless_boot = false;

	for (i = 0; i < context->stream_count; i++) {
		if (context->streams[i]->apply_seamless_boot_optimization) {
			can_apply_seamless_boot = true;
			break;
		}
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* There is assumption that pipe_ctx is not mapping irregularly
		 * to non-preferred front end. If pipe_ctx->stream is not NULL,
		 * we will use the pipe, so don't disable
		 */
		if (pipe_ctx->stream != NULL && can_apply_seamless_boot)
			continue;

		/* Blank controller using driver code instead of
		 * command table.
		 */
		if (tg->funcs->is_tg_enabled(tg)) {
			if (dc->hwss.init_blank != NULL) {
				dc->hwss.init_blank(dc, tg);
				tg->funcs->lock(tg);
			} else {
				tg->funcs->lock(tg);
				tg->funcs->set_blank(tg, true);
				hwss_wait_for_blank_complete(tg);
			}
		}
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* Cannot reset the MPC mux if seamless boot */
		if (pipe_ctx->stream != NULL && can_apply_seamless_boot)
			continue;

		dc->res_pool->mpc->funcs->mpc_init_single_inst(
				dc->res_pool->mpc, i);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];
		struct hubp *hubp = dc->res_pool->hubps[i];
		struct dpp *dpp = dc->res_pool->dpps[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* There is assumption that pipe_ctx is not mapping irregularly
		 * to non-preferred front end. If pipe_ctx->stream is not NULL,
		 * we will use the pipe, so don't disable
		 */
		if (can_apply_seamless_boot &&
			pipe_ctx->stream != NULL &&
			pipe_ctx->stream_res.tg->funcs->is_tg_enabled(
				pipe_ctx->stream_res.tg))
			continue;

		/* Disable on the current state so the new one isn't cleared. */
		pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];

		dpp->funcs->dpp_reset(dpp);

		pipe_ctx->stream_res.tg = tg;
		pipe_ctx->pipe_idx = i;

		pipe_ctx->plane_res.hubp = hubp;
		pipe_ctx->plane_res.dpp = dpp;
		pipe_ctx->plane_res.mpcc_inst = dpp->inst;
		hubp->mpcc_id = dpp->inst;
		hubp->opp_id = OPP_ID_INVALID;
		hubp->power_gated = false;

		dc->res_pool->opps[i]->mpc_tree_params.opp_id = dc->res_pool->opps[i]->inst;
		dc->res_pool->opps[i]->mpc_tree_params.opp_list = NULL;
		dc->res_pool->opps[i]->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;
		pipe_ctx->stream_res.opp = dc->res_pool->opps[i];

		dc->hwss.plane_atomic_disconnect(dc, pipe_ctx);

		if (tg->funcs->is_tg_enabled(tg))
			tg->funcs->unlock(tg);

		dc->hwss.disable_plane(dc, pipe_ctx);

		pipe_ctx->stream_res.tg = NULL;
		pipe_ctx->plane_res.hubp = NULL;

		tg->funcs->tg_init(tg);
	}
}