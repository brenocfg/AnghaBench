#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct pp_smu_funcs_rv {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_pme_wa_enable ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_24__ {TYPE_10__* audio; TYPE_11__* stream_enc; } ;
struct pipe_ctx {TYPE_8__ stream_res; TYPE_4__* stream; } ;
struct TYPE_22__ {int dynamic_audio; } ;
struct TYPE_18__ {int /*<<< orphan*/  az_endpoint_mute_only; } ;
struct dc {TYPE_9__* res_pool; TYPE_7__* current_state; TYPE_6__ caps; TYPE_2__ debug; } ;
struct TYPE_25__ {struct pp_smu_funcs_rv* pp_smu; } ;
struct TYPE_23__ {int /*<<< orphan*/  res_ctx; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* hdmi_audio_disable ) (TYPE_11__*) ;int /*<<< orphan*/  (* dp_audio_disable ) (TYPE_11__*) ;int /*<<< orphan*/  (* audio_mute_control ) (TYPE_11__*,int) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  signal; TYPE_1__* ctx; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* az_disable ) (TYPE_10__*) ;} ;
struct TYPE_17__ {struct dc* dc; } ;
struct TYPE_16__ {TYPE_5__* funcs; } ;
struct TYPE_15__ {TYPE_3__* funcs; } ;

/* Variables and functions */
 int FREE_ACQUIRED_RESOURCE ; 
 int KEEP_ACQUIRED_RESOURCE ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_11__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_11__*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_audio_usage (int /*<<< orphan*/ *,TYPE_9__*,TYPE_10__*,int) ; 

void dce110_disable_audio_stream(struct pipe_ctx *pipe_ctx, int option)
{
	struct dc *dc = pipe_ctx->stream->ctx->dc;

	pipe_ctx->stream_res.stream_enc->funcs->audio_mute_control(
			pipe_ctx->stream_res.stream_enc, true);
	if (pipe_ctx->stream_res.audio) {
		struct pp_smu_funcs_rv *pp_smu = dc->res_pool->pp_smu;

		if (option != KEEP_ACQUIRED_RESOURCE ||
				!dc->debug.az_endpoint_mute_only) {
			/*only disalbe az_endpoint if power down or free*/
			pipe_ctx->stream_res.audio->funcs->az_disable(pipe_ctx->stream_res.audio);
		}

		if (dc_is_dp_signal(pipe_ctx->stream->signal))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_disable(
					pipe_ctx->stream_res.stream_enc);
		else
			pipe_ctx->stream_res.stream_enc->funcs->hdmi_audio_disable(
					pipe_ctx->stream_res.stream_enc);
		/*don't free audio if it is from retrain or internal disable stream*/
		if (option == FREE_ACQUIRED_RESOURCE && dc->caps.dynamic_audio == true) {
			/*we have to dynamic arbitrate the audio endpoints*/
			/*we free the resource, need reset is_audio_acquired*/
			update_audio_usage(&dc->current_state->res_ctx, dc->res_pool, pipe_ctx->stream_res.audio, false);
			pipe_ctx->stream_res.audio = NULL;
		}
		if (pp_smu != NULL && pp_smu->set_pme_wa_enable != NULL)
			/*this is the first audio. apply the PME w/a in order to wake AZ from D3*/
			pp_smu->set_pme_wa_enable(&pp_smu->pp_smu);

		/* TODO: notify audio driver for if audio modes list changed
		 * add audio mode list change flag */
		/* dal_audio_disable_azalia_audio_jack_presence(stream->audio,
		 * stream->stream_engine_id);
		 */
	}
}