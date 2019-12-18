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
typedef  int uint32_t ;
struct timing_generator {TYPE_8__* funcs; } ;
struct TYPE_18__ {TYPE_17__* hubp; } ;
struct TYPE_30__ {struct timing_generator* tg; } ;
struct pipe_ctx {int /*<<< orphan*/  ttu_regs; int /*<<< orphan*/  dlg_regs; TYPE_10__ plane_res; TYPE_7__* plane_state; struct dc_stream_state const* stream; int /*<<< orphan*/  pipe_idx; TYPE_5__ stream_res; } ;
struct dc_stream_state {scalar_t__ num_wb_info; } ;
struct TYPE_31__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_6__ res_ctx; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* optimize_bandwidth ) (struct dc*,struct dc_state*) ;int /*<<< orphan*/  (* disable_plane ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* program_all_writeback_pipes_in_tree ) (struct dc*,struct dc_stream_state const*,struct dc_state*) ;int /*<<< orphan*/  (* plane_atomic_disconnect ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* blank_pixel_data ) (struct dc*,struct pipe_ctx*,int) ;int /*<<< orphan*/  (* did_underflow_occur ) (struct dc*,struct pipe_ctx*) ;} ;
struct TYPE_29__ {int underflow_assert_delay_us; } ;
struct dc {TYPE_16__* res_pool; TYPE_15__* hwseq; TYPE_13__ hwss; TYPE_12__* current_state; TYPE_4__ debug; TYPE_1__* ctx; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* hubp_setup_interdependent ) (TYPE_17__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_33__ {int /*<<< orphan*/  (* is_tg_enabled ) (struct timing_generator*) ;} ;
struct TYPE_27__ {scalar_t__ full_update; } ;
struct TYPE_28__ {TYPE_2__ bits; } ;
struct TYPE_32__ {TYPE_3__ update_flags; } ;
struct TYPE_26__ {int /*<<< orphan*/  logger; } ;
struct TYPE_25__ {scalar_t__ opp_id; TYPE_9__* funcs; } ;
struct TYPE_24__ {int pipe_count; int /*<<< orphan*/  hubbub; } ;
struct TYPE_22__ {scalar_t__ DEGVIDCN10_254; } ;
struct TYPE_23__ {TYPE_14__ wa; } ;
struct TYPE_19__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_20__ {TYPE_11__ res_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DC (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ OPP_ID_INVALID ; 
 int /*<<< orphan*/  dcn10_pipe_control_lock (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  false_optc_underflow_wa (struct dc*,struct dc_stream_state const*,struct timing_generator*) ; 
 struct pipe_ctx* find_top_pipe_for_stream (struct dc*,struct dc_state*,struct dc_stream_state const*) ; 
 int /*<<< orphan*/  hubbub1_wm_change_req_wa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_all_pipes (struct dc*,struct dc_state*,int) ; 
 int /*<<< orphan*/  program_all_pipe_in_tree (struct dc*,struct pipe_ctx*,struct dc_state*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub10 (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  stub2 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub3 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub4 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub5 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub6 (struct dc*,struct dc_stream_state const*,struct dc_state*) ; 
 int /*<<< orphan*/  stub7 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub8 (TYPE_17__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dcn10_apply_ctx_for_surface(
		struct dc *dc,
		const struct dc_stream_state *stream,
		int num_planes,
		struct dc_state *context)
{
	int i;
	struct timing_generator *tg;
	uint32_t underflow_check_delay_us;
	bool removed_pipe[4] = { false };
	bool interdependent_update = false;
	struct pipe_ctx *top_pipe_to_program =
			find_top_pipe_for_stream(dc, context, stream);
	DC_LOGGER_INIT(dc->ctx->logger);

	if (!top_pipe_to_program)
		return;

	tg = top_pipe_to_program->stream_res.tg;

	interdependent_update = top_pipe_to_program->plane_state &&
		top_pipe_to_program->plane_state->update_flags.bits.full_update;

	underflow_check_delay_us = dc->debug.underflow_assert_delay_us;

	if (underflow_check_delay_us != 0xFFFFFFFF && dc->hwss.did_underflow_occur)
		ASSERT(dc->hwss.did_underflow_occur(dc, top_pipe_to_program));

	if (interdependent_update)
		lock_all_pipes(dc, context, true);
	else
		dcn10_pipe_control_lock(dc, top_pipe_to_program, true);

	if (underflow_check_delay_us != 0xFFFFFFFF)
		udelay(underflow_check_delay_us);

	if (underflow_check_delay_us != 0xFFFFFFFF && dc->hwss.did_underflow_occur)
		ASSERT(dc->hwss.did_underflow_occur(dc, top_pipe_to_program));

	if (num_planes == 0) {
		/* OTG blank before remove all front end */
		dc->hwss.blank_pixel_data(dc, top_pipe_to_program, true);
	}

	/* Disconnect unused mpcc */
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		struct pipe_ctx *old_pipe_ctx =
				&dc->current_state->res_ctx.pipe_ctx[i];
		/*
		 * Powergate reused pipes that are not powergated
		 * fairly hacky right now, using opp_id as indicator
		 * TODO: After move dc_post to dc_update, this will
		 * be removed.
		 */
		if (pipe_ctx->plane_state && !old_pipe_ctx->plane_state) {
			if (old_pipe_ctx->stream_res.tg == tg &&
			    old_pipe_ctx->plane_res.hubp &&
			    old_pipe_ctx->plane_res.hubp->opp_id != OPP_ID_INVALID)
				dc->hwss.disable_plane(dc, old_pipe_ctx);
		}

		if ((!pipe_ctx->plane_state ||
		     pipe_ctx->stream_res.tg != old_pipe_ctx->stream_res.tg) &&
		    old_pipe_ctx->plane_state &&
		    old_pipe_ctx->stream_res.tg == tg) {

			dc->hwss.plane_atomic_disconnect(dc, old_pipe_ctx);
			removed_pipe[i] = true;

			DC_LOG_DC("Reset mpcc for pipe %d\n",
					old_pipe_ctx->pipe_idx);
		}
	}

	if (num_planes > 0)
		program_all_pipe_in_tree(dc, top_pipe_to_program, context);

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	/* Program secondary blending tree and writeback pipes */
	if ((stream->num_wb_info > 0) && (dc->hwss.program_all_writeback_pipes_in_tree))
		dc->hwss.program_all_writeback_pipes_in_tree(dc, stream, context);
#endif
	if (interdependent_update)
		for (i = 0; i < dc->res_pool->pipe_count; i++) {
			struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
			/* Skip inactive pipes and ones already updated */
			if (!pipe_ctx->stream || pipe_ctx->stream == stream ||
			    !pipe_ctx->plane_state || !tg->funcs->is_tg_enabled(tg))
				continue;

			pipe_ctx->plane_res.hubp->funcs->hubp_setup_interdependent(
				pipe_ctx->plane_res.hubp,
				&pipe_ctx->dlg_regs,
				&pipe_ctx->ttu_regs);
		}

	if (interdependent_update)
		lock_all_pipes(dc, context, false);
	else
		dcn10_pipe_control_lock(dc, top_pipe_to_program, false);

	if (num_planes == 0)
		false_optc_underflow_wa(dc, stream, tg);

	for (i = 0; i < dc->res_pool->pipe_count; i++)
		if (removed_pipe[i])
			dc->hwss.disable_plane(dc, &dc->current_state->res_ctx.pipe_ctx[i]);

	for (i = 0; i < dc->res_pool->pipe_count; i++)
		if (removed_pipe[i]) {
			dc->hwss.optimize_bandwidth(dc, context);
			break;
		}

	if (dc->hwseq->wa.DEGVIDCN10_254)
		hubbub1_wm_change_req_wa(dc->res_pool->hubbub);
}