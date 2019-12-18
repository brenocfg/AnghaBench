#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct timing_generator {TYPE_9__* funcs; } ;
struct resource_pool {int timing_generator_count; int pipe_count; struct timing_generator** timing_generators; int /*<<< orphan*/ * mcif_wb; TYPE_2__** dwbc; TYPE_12__* res_cap; TYPE_14__** opps; struct dpp** dpps; struct hubp** hubps; TYPE_15__* mpc; TYPE_16__* dccg; } ;
struct TYPE_30__ {size_t mpcc_inst; struct hubp* hubp; struct dpp* dpp; } ;
struct TYPE_29__ {struct timing_generator* tg; TYPE_14__* opp; } ;
struct pipe_ctx {int pipe_idx; TYPE_5__ plane_res; TYPE_4__ stream_res; } ;
struct hubp {size_t mpcc_id; int power_gated; TYPE_1__* funcs; int /*<<< orphan*/  opp_id; } ;
struct dpp {size_t inst; TYPE_10__* funcs; } ;
struct dce_hwseq {int dummy; } ;
struct TYPE_28__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_3__ res_ctx; } ;
struct TYPE_33__ {int /*<<< orphan*/  (* disable_plane ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* enable_power_gating_plane ) (struct dce_hwseq*,int) ;} ;
struct dc {struct resource_pool* res_pool; TYPE_8__ hwss; TYPE_17__* clk_mgr; struct dc_state* current_state; struct dce_hwseq* hwseq; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* tg_init ) (struct timing_generator*) ;int /*<<< orphan*/  (* unlock ) (struct timing_generator*) ;scalar_t__ (* is_tg_enabled ) (struct timing_generator*) ;int /*<<< orphan*/  (* lock ) (struct timing_generator*) ;} ;
struct TYPE_32__ {int /*<<< orphan*/  (* dccg_init ) (TYPE_16__*) ;} ;
struct TYPE_31__ {int /*<<< orphan*/  (* init_clocks ) (TYPE_17__*) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  mcif; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* hubp_init ) (struct hubp*) ;} ;
struct TYPE_25__ {TYPE_6__* funcs; } ;
struct TYPE_24__ {TYPE_7__* funcs; } ;
struct TYPE_23__ {TYPE_11__* funcs; } ;
struct TYPE_21__ {int /*<<< orphan*/ * opp_list; int /*<<< orphan*/  opp_id; } ;
struct TYPE_22__ {int* mpcc_disconnect_pending; TYPE_13__ mpc_tree_params; int /*<<< orphan*/  inst; } ;
struct TYPE_20__ {int num_opp; int num_dwb; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* mpc_init ) (TYPE_15__*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* dpp_reset ) (struct dpp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_ENABLE ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_REFDIV ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  OPP_ID_INVALID ; 
 int /*<<< orphan*/  RBBMIF_TIMEOUT_DIS ; 
 int /*<<< orphan*/  RBBMIF_TIMEOUT_DIS_2 ; 
 int /*<<< orphan*/  REFCLK_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dcn20_dccg_init (struct dce_hwseq*) ; 
 int /*<<< orphan*/  dcn20_init_blank (struct dc*,struct timing_generator*) ; 
 int /*<<< orphan*/  hwss1_plane_atomic_disconnect (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (TYPE_17__*) ; 
 scalar_t__ stub10 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub11 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub12 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub13 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub2 (TYPE_16__*) ; 
 int /*<<< orphan*/  stub3 (struct dce_hwseq*,int) ; 
 scalar_t__ stub4 (struct timing_generator*) ; 
 scalar_t__ stub5 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub6 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub7 (struct dpp*) ; 
 int /*<<< orphan*/  stub8 (TYPE_15__*) ; 
 int /*<<< orphan*/  stub9 (struct hubp*) ; 

__attribute__((used)) static void dcn20_fpga_init_hw(struct dc *dc)
{
	int i, j;
	struct dce_hwseq *hws = dc->hwseq;
	struct resource_pool *res_pool = dc->res_pool;
	struct dc_state  *context = dc->current_state;

	if (dc->clk_mgr && dc->clk_mgr->funcs->init_clocks)
		dc->clk_mgr->funcs->init_clocks(dc->clk_mgr);

	// Initialize the dccg
	if (res_pool->dccg->funcs->dccg_init)
		res_pool->dccg->funcs->dccg_init(res_pool->dccg);

	//Enable ability to power gate / don't force power on permanently
	dc->hwss.enable_power_gating_plane(hws, true);

	// Specific to FPGA dccg and registers
	REG_WRITE(RBBMIF_TIMEOUT_DIS, 0xFFFFFFFF);
	REG_WRITE(RBBMIF_TIMEOUT_DIS_2, 0xFFFFFFFF);

	dcn20_dccg_init(hws);

	REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_REFDIV, 2);
	REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_ENABLE, 1);
	REG_WRITE(REFCLK_CNTL, 0);
	//


	/* Blank pixel data with OPP DPG */
	for (i = 0; i < dc->res_pool->timing_generator_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->is_tg_enabled(tg))
			dcn20_init_blank(dc, tg);
	}

	for (i = 0; i < res_pool->timing_generator_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->is_tg_enabled(tg))
			tg->funcs->lock(tg);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct dpp *dpp = res_pool->dpps[i];

		dpp->funcs->dpp_reset(dpp);
	}

	/* Reset all MPCC muxes */
	res_pool->mpc->funcs->mpc_init(res_pool->mpc);

	/* initialize OPP mpc_tree parameter */
	for (i = 0; i < dc->res_pool->res_cap->num_opp; i++) {
		res_pool->opps[i]->mpc_tree_params.opp_id = res_pool->opps[i]->inst;
		res_pool->opps[i]->mpc_tree_params.opp_list = NULL;
		for (j = 0; j < MAX_PIPES; j++)
			res_pool->opps[i]->mpcc_disconnect_pending[j] = false;
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		struct hubp *hubp = dc->res_pool->hubps[i];
		struct dpp *dpp = dc->res_pool->dpps[i];

		pipe_ctx->stream_res.tg = tg;
		pipe_ctx->pipe_idx = i;

		pipe_ctx->plane_res.hubp = hubp;
		pipe_ctx->plane_res.dpp = dpp;
		pipe_ctx->plane_res.mpcc_inst = dpp->inst;
		hubp->mpcc_id = dpp->inst;
		hubp->opp_id = OPP_ID_INVALID;
		hubp->power_gated = false;
		pipe_ctx->stream_res.opp = NULL;

		hubp->funcs->hubp_init(hubp);

		//dc->res_pool->opps[i]->mpc_tree_params.opp_id = dc->res_pool->opps[i]->inst;
		//dc->res_pool->opps[i]->mpc_tree_params.opp_list = NULL;
		dc->res_pool->opps[i]->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;
		pipe_ctx->stream_res.opp = dc->res_pool->opps[i];
		/*to do*/
		hwss1_plane_atomic_disconnect(dc, pipe_ctx);
	}

	/* initialize DWB pointer to MCIF_WB */
	for (i = 0; i < res_pool->res_cap->num_dwb; i++)
		res_pool->dwbc[i]->mcif = res_pool->mcif_wb[i];

	for (i = 0; i < dc->res_pool->timing_generator_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->is_tg_enabled(tg))
			tg->funcs->unlock(tg);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		dc->hwss.disable_plane(dc, pipe_ctx);

		pipe_ctx->stream_res.tg = NULL;
		pipe_ctx->plane_res.hubp = NULL;
	}

	for (i = 0; i < dc->res_pool->timing_generator_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		tg->funcs->tg_init(tg);
	}
}