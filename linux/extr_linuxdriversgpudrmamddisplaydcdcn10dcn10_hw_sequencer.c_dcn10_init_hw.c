#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct timing_generator {TYPE_16__* funcs; } ;
struct TYPE_36__ {size_t mpcc_inst; struct hubp* hubp; struct dpp* dpp; } ;
struct TYPE_35__ {struct timing_generator* tg; TYPE_2__* opp; } ;
struct pipe_ctx {int pipe_idx; TYPE_5__ plane_res; TYPE_4__ stream_res; } ;
struct hubp {size_t mpcc_id; int opp_id; int power_gated; } ;
struct dpp {size_t inst; } ;
struct dmcu {TYPE_8__* funcs; } ;
struct dce_hwseq {int dummy; } ;
struct TYPE_34__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_3__ res_ctx; } ;
struct dc_link {TYPE_20__* link_enc; } ;
struct dc_bios {TYPE_12__* funcs; } ;
struct TYPE_22__ {int /*<<< orphan*/  disable_clock_gate; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* edp_power_control ) (struct dc_link*,int) ;} ;
struct dc {int link_count; TYPE_18__* res_pool; struct dce_hwseq* hwseq; TYPE_11__ debug; TYPE_10__* ctx; TYPE_14__ hwss; struct dc_link** links; struct dc_state* current_state; } ;
struct audio {TYPE_6__* funcs; } ;
struct abm {TYPE_7__* funcs; } ;
struct TYPE_40__ {int /*<<< orphan*/  clks; } ;
struct TYPE_39__ {int /*<<< orphan*/  (* dmcu_init ) (struct dmcu*) ;} ;
struct TYPE_38__ {int /*<<< orphan*/  (* abm_init ) (struct abm*) ;int /*<<< orphan*/  (* init_backlight ) (struct abm*) ;} ;
struct TYPE_37__ {int /*<<< orphan*/  (* hw_init ) (struct audio*) ;} ;
struct TYPE_31__ {int /*<<< orphan*/ * opp_list; int /*<<< orphan*/  opp_id; } ;
struct TYPE_33__ {int* mpcc_disconnect_pending; TYPE_1__ mpc_tree_params; int /*<<< orphan*/  inst; } ;
struct TYPE_24__ {scalar_t__ id; } ;
struct TYPE_32__ {TYPE_15__* funcs; TYPE_13__ connector; } ;
struct TYPE_30__ {TYPE_17__* funcs; } ;
struct TYPE_29__ {int pipe_count; int timing_generator_count; int audio_count; TYPE_9__* dccg; struct audio** audios; struct timing_generator** timing_generators; TYPE_2__** opps; struct dpp** dpps; struct hubp** hubps; TYPE_19__* mpc; struct dmcu* dmcu; struct abm* abm; } ;
struct TYPE_28__ {int /*<<< orphan*/  (* mpc_init ) (TYPE_19__*) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  (* tg_init ) (struct timing_generator*) ;int /*<<< orphan*/  (* unlock ) (struct timing_generator*) ;scalar_t__ (* is_tg_enabled ) (struct timing_generator*) ;int /*<<< orphan*/  (* set_blank ) (struct timing_generator*,int) ;int /*<<< orphan*/  (* lock ) (struct timing_generator*) ;} ;
struct TYPE_26__ {int /*<<< orphan*/  (* hw_init ) (TYPE_20__*) ;} ;
struct TYPE_23__ {int /*<<< orphan*/  (* is_accelerated_mode ) (struct dc_bios*) ;} ;
struct TYPE_21__ {int /*<<< orphan*/  dce_environment; struct dc_bios* dc_bios; } ;

/* Variables and functions */
 scalar_t__ CONNECTOR_ID_EDP ; 
 int /*<<< orphan*/  DCCG_GATE_DISABLE_CNTL ; 
 int /*<<< orphan*/  DCCG_GATE_DISABLE_CNTL2 ; 
 int /*<<< orphan*/  DCFCLK_CNTL ; 
 int /*<<< orphan*/  DCFCLK_GATE_DIS ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_GLOBAL_TIMER_ENABLE ; 
 int /*<<< orphan*/  DIO_MEM_PWR_CTRL ; 
 scalar_t__ IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REFCLK_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bios_golden_init (struct dc*) ; 
 int /*<<< orphan*/  dcn10_disable_plane (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  disable_vga (struct dce_hwseq*) ; 
 int /*<<< orphan*/  enable_power_gating_plane (struct dce_hwseq*,int) ; 
 int /*<<< orphan*/  hwss1_plane_atomic_disconnect (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  hwss_wait_for_blank_complete (struct timing_generator*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc_bios*) ; 
 int /*<<< orphan*/  stub10 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub11 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub12 (struct audio*) ; 
 int /*<<< orphan*/  stub13 (struct abm*) ; 
 int /*<<< orphan*/  stub14 (struct abm*) ; 
 int /*<<< orphan*/  stub15 (struct dmcu*) ; 
 int /*<<< orphan*/  stub2 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_20__*) ; 
 scalar_t__ stub4 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub5 (struct timing_generator*) ; 
 scalar_t__ stub6 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub7 (struct timing_generator*,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_19__*) ; 
 scalar_t__ stub9 (struct timing_generator*) ; 

__attribute__((used)) static void dcn10_init_hw(struct dc *dc)
{
	int i;
	struct abm *abm = dc->res_pool->abm;
	struct dmcu *dmcu = dc->res_pool->dmcu;
	struct dce_hwseq *hws = dc->hwseq;
	struct dc_bios *dcb = dc->ctx->dc_bios;
	struct dc_state  *context = dc->current_state;

	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {
		REG_WRITE(REFCLK_CNTL, 0);
		REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_ENABLE, 1);
		REG_WRITE(DIO_MEM_PWR_CTRL, 0);

		if (!dc->debug.disable_clock_gate) {
			/* enable all DCN clock gating */
			REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

			REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

			REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
		}

		enable_power_gating_plane(dc->hwseq, true);
	} else {

		if (!dcb->funcs->is_accelerated_mode(dcb)) {
			bios_golden_init(dc);
			disable_vga(dc->hwseq);
		}

		for (i = 0; i < dc->link_count; i++) {
			/* Power up AND update implementation according to the
			 * required signal (which may be different from the
			 * default signal on connector).
			 */
			struct dc_link *link = dc->links[i];

			if (link->link_enc->connector.id == CONNECTOR_ID_EDP)
				dc->hwss.edp_power_control(link, true);

			link->link_enc->funcs->hw_init(link->link_enc);
		}
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->is_tg_enabled(tg))
			tg->funcs->lock(tg);
	}

	/* Blank controller using driver code instead of
	 * command table.
	 */
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->is_tg_enabled(tg)) {
			tg->funcs->set_blank(tg, true);
			hwss_wait_for_blank_complete(tg);
		}
	}

	/* Reset all MPCC muxes */
	dc->res_pool->mpc->funcs->mpc_init(dc->res_pool->mpc);

	for (i = 0; i < dc->res_pool->timing_generator_count; i++) {
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
		hubp->opp_id = 0xf;
		hubp->power_gated = false;

		dc->res_pool->opps[i]->mpc_tree_params.opp_id = dc->res_pool->opps[i]->inst;
		dc->res_pool->opps[i]->mpc_tree_params.opp_list = NULL;
		dc->res_pool->opps[i]->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;
		pipe_ctx->stream_res.opp = dc->res_pool->opps[i];

		hwss1_plane_atomic_disconnect(dc, pipe_ctx);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];

		if (tg->funcs->is_tg_enabled(tg))
			tg->funcs->unlock(tg);
	}

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct timing_generator *tg = dc->res_pool->timing_generators[i];
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		dcn10_disable_plane(dc, pipe_ctx);

		pipe_ctx->stream_res.tg = NULL;
		pipe_ctx->plane_res.hubp = NULL;

		tg->funcs->tg_init(tg);
	}

	/* end of FPGA. Below if real ASIC */
	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment))
		return;

	for (i = 0; i < dc->res_pool->audio_count; i++) {
		struct audio *audio = dc->res_pool->audios[i];

		audio->funcs->hw_init(audio);
	}

	if (abm != NULL) {
		abm->funcs->init_backlight(abm);
		abm->funcs->abm_init(abm);
	}

	if (dmcu != NULL)
		dmcu->funcs->dmcu_init(dmcu);

	/* power AFMT HDMI memory TODO: may move to dis/en output save power*/
	REG_WRITE(DIO_MEM_PWR_CTRL, 0);

	if (!dc->debug.disable_clock_gate) {
		/* enable all DCN clock gating */
		REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

		REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

		REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
	}

	enable_power_gating_plane(dc->hwseq, true);

	memset(&dc->res_pool->dccg->clks, 0, sizeof(dc->res_pool->dccg->clks));
}