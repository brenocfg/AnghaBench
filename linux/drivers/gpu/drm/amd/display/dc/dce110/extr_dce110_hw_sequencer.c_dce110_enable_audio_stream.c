#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct pp_smu_funcs {int dummy; } ;
struct TYPE_15__ {TYPE_13__* audio; TYPE_12__* stream_enc; } ;
struct pipe_ctx {TYPE_11__ stream_res; TYPE_2__* stream; } ;
struct dc {TYPE_7__* current_state; TYPE_3__* res_pool; struct clk_mgr* clk_mgr; } ;
struct clk_mgr {TYPE_9__* funcs; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* enable_pme_wa ) (struct clk_mgr*) ;} ;
struct TYPE_25__ {int /*<<< orphan*/  (* az_enable ) (TYPE_13__*) ;} ;
struct TYPE_23__ {TYPE_5__* pipe_ctx; } ;
struct TYPE_24__ {TYPE_6__ res_ctx; } ;
struct TYPE_21__ {int /*<<< orphan*/ * audio; } ;
struct TYPE_22__ {TYPE_4__ stream_res; } ;
struct TYPE_20__ {struct pp_smu_funcs* pp_smu; } ;
struct TYPE_19__ {TYPE_1__* ctx; } ;
struct TYPE_18__ {struct dc* dc; } ;
struct TYPE_17__ {int enabled; TYPE_8__* funcs; } ;
struct TYPE_16__ {TYPE_10__* funcs; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* audio_mute_control ) (TYPE_12__*,int) ;} ;

/* Variables and functions */
 unsigned int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (TYPE_13__*) ; 
 int /*<<< orphan*/  stub2 (struct clk_mgr*) ; 
 int /*<<< orphan*/  stub3 (TYPE_12__*,int) ; 

void dce110_enable_audio_stream(struct pipe_ctx *pipe_ctx)
{
	/* notify audio driver for audio modes of monitor */
	struct dc *core_dc;
	struct pp_smu_funcs *pp_smu = NULL;
	struct clk_mgr *clk_mgr;
	unsigned int i, num_audio = 1;

	if (!pipe_ctx->stream)
		return;

	core_dc = pipe_ctx->stream->ctx->dc;
	clk_mgr = core_dc->clk_mgr;

	if (pipe_ctx->stream_res.audio && pipe_ctx->stream_res.audio->enabled == true)
		return;

	if (core_dc->res_pool->pp_smu)
		pp_smu = core_dc->res_pool->pp_smu;

	if (pipe_ctx->stream_res.audio) {
		for (i = 0; i < MAX_PIPES; i++) {
			/*current_state not updated yet*/
			if (core_dc->current_state->res_ctx.pipe_ctx[i].stream_res.audio != NULL)
				num_audio++;
		}

		pipe_ctx->stream_res.audio->funcs->az_enable(pipe_ctx->stream_res.audio);

		if (num_audio >= 1 && clk_mgr->funcs->enable_pme_wa)
			/*this is the first audio. apply the PME w/a in order to wake AZ from D3*/
			clk_mgr->funcs->enable_pme_wa(clk_mgr);
		/* un-mute audio */
		/* TODO: audio should be per stream rather than per link */
		pipe_ctx->stream_res.stream_enc->funcs->audio_mute_control(
					pipe_ctx->stream_res.stream_enc, false);
		if (pipe_ctx->stream_res.audio)
			pipe_ctx->stream_res.audio->enabled = true;
	}
}