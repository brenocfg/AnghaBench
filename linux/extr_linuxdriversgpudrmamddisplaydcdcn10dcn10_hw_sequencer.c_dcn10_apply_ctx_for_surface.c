#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct timing_generator {TYPE_5__* funcs; } ;
struct TYPE_21__ {struct timing_generator* tg; } ;
struct TYPE_19__ {TYPE_3__* hubp; } ;
struct pipe_ctx {int /*<<< orphan*/  pipe_idx; TYPE_6__ stream_res; scalar_t__ plane_state; TYPE_4__ plane_res; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_17__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_2__ res_ctx; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* plane_atomic_disconnect ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* blank_pixel_data ) (struct dc*,struct pipe_ctx*,int) ;} ;
struct dc {TYPE_12__* res_pool; TYPE_11__* hwseq; TYPE_9__* current_state; TYPE_7__ hwss; TYPE_1__* ctx; } ;
struct TYPE_23__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_24__ {TYPE_8__ res_ctx; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* lock ) (struct timing_generator*) ;} ;
struct TYPE_18__ {int opp_id; } ;
struct TYPE_16__ {int /*<<< orphan*/  logger; } ;
struct TYPE_15__ {int pipe_count; int /*<<< orphan*/  hubbub; } ;
struct TYPE_13__ {scalar_t__ DEGVIDCN10_254; } ;
struct TYPE_14__ {TYPE_10__ wa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcn10_disable_plane (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  dcn10_pipe_control_lock (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  false_optc_underflow_wa (struct dc*,struct dc_stream_state const*,struct timing_generator*) ; 
 struct pipe_ctx* find_top_pipe_for_stream (struct dc*,struct dc_state*,struct dc_stream_state const*) ; 
 int /*<<< orphan*/  hubbub1_wm_change_req_wa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_all_pipe_in_tree (struct dc*,struct pipe_ctx*,struct dc_state*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub3 (struct dc*,struct pipe_ctx*) ; 

__attribute__((used)) static void dcn10_apply_ctx_for_surface(
		struct dc *dc,
		const struct dc_stream_state *stream,
		int num_planes,
		struct dc_state *context)
{
	int i;
	struct timing_generator *tg;
	bool removed_pipe[4] = { false };
	struct pipe_ctx *top_pipe_to_program =
			find_top_pipe_for_stream(dc, context, stream);
	DC_LOGGER_INIT(dc->ctx->logger);

	if (!top_pipe_to_program)
		return;

	tg = top_pipe_to_program->stream_res.tg;

	dcn10_pipe_control_lock(dc, top_pipe_to_program, true);

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
				old_pipe_ctx->plane_res.hubp->opp_id != 0xf) {
				dcn10_disable_plane(dc, old_pipe_ctx);
				/*
				 * power down fe will unlock when calling reset, need
				 * to lock it back here. Messy, need rework.
				 */
				pipe_ctx->stream_res.tg->funcs->lock(pipe_ctx->stream_res.tg);
			}
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

	dcn10_pipe_control_lock(dc, top_pipe_to_program, false);

	if (num_planes == 0)
		false_optc_underflow_wa(dc, stream, tg);

	for (i = 0; i < dc->res_pool->pipe_count; i++)
		if (removed_pipe[i])
			dcn10_disable_plane(dc, &dc->current_state->res_ctx.pipe_ctx[i]);

	if (dc->hwseq->wa.DEGVIDCN10_254)
		hubbub1_wm_change_req_wa(dc->res_pool->hubbub);
}