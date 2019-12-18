#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct pp_smu_funcs {int dummy; } ;
struct TYPE_16__ {TYPE_8__* stream_enc; TYPE_2__* audio; } ;
struct pipe_ctx {TYPE_6__ stream_res; TYPE_4__* stream; } ;
struct dc {TYPE_3__* res_pool; struct clk_mgr* clk_mgr; } ;
struct clk_mgr {TYPE_7__* funcs; } ;
struct TYPE_18__ {TYPE_5__* funcs; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* enable_pme_wa ) (struct clk_mgr*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  (* hdmi_audio_disable ) (TYPE_8__*) ;int /*<<< orphan*/  (* dp_audio_disable ) (TYPE_8__*) ;int /*<<< orphan*/  (* audio_mute_control ) (TYPE_8__*,int) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  signal; TYPE_1__* ctx; } ;
struct TYPE_13__ {struct pp_smu_funcs* pp_smu; } ;
struct TYPE_12__ {int enabled; } ;
struct TYPE_11__ {struct dc* dc; } ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub4 (struct clk_mgr*) ; 

void dce110_disable_audio_stream(struct pipe_ctx *pipe_ctx)
{
	struct dc *dc;
	struct pp_smu_funcs *pp_smu = NULL;
	struct clk_mgr *clk_mgr;

	if (!pipe_ctx || !pipe_ctx->stream)
		return;

	dc = pipe_ctx->stream->ctx->dc;
	clk_mgr = dc->clk_mgr;

	if (pipe_ctx->stream_res.audio && pipe_ctx->stream_res.audio->enabled == false)
		return;

	pipe_ctx->stream_res.stream_enc->funcs->audio_mute_control(
			pipe_ctx->stream_res.stream_enc, true);
	if (pipe_ctx->stream_res.audio) {
		pipe_ctx->stream_res.audio->enabled = false;

		if (dc->res_pool->pp_smu)
			pp_smu = dc->res_pool->pp_smu;

		if (dc_is_dp_signal(pipe_ctx->stream->signal))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_disable(
					pipe_ctx->stream_res.stream_enc);
		else
			pipe_ctx->stream_res.stream_enc->funcs->hdmi_audio_disable(
					pipe_ctx->stream_res.stream_enc);

		if (clk_mgr->funcs->enable_pme_wa)
			/*this is the first audio. apply the PME w/a in order to wake AZ from D3*/
			clk_mgr->funcs->enable_pme_wa(clk_mgr);

		/* TODO: notify audio driver for if audio modes list changed
		 * add audio mode list change flag */
		/* dal_audio_disable_azalia_audio_jack_presence(stream->audio,
		 * stream->stream_engine_id);
		 */
	}
}