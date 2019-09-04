#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_6__* audio; } ;
struct pipe_ctx {TYPE_5__* stream; TYPE_4__ stream_res; scalar_t__ top_pipe; } ;
struct TYPE_9__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_2__ res_ctx; } ;
struct dc {TYPE_1__* res_pool; } ;
struct audio_output {int /*<<< orphan*/  pll_info; int /*<<< orphan*/  crtc_info; } ;
struct TYPE_13__ {TYPE_3__* funcs; } ;
struct TYPE_12__ {scalar_t__ signal; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* wall_dto_setup ) (TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int pipe_count; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_HDMI_TYPE_A ; 
 int /*<<< orphan*/  build_audio_output (struct dc_state*,struct pipe_ctx*,struct audio_output*) ; 
 int /*<<< orphan*/  dc_is_dp_signal (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dce110_setup_audio_dto(
		struct dc *dc,
		struct dc_state *context)
{
	int i;

	/* program audio wall clock. use HDMI as clock source if HDMI
	 * audio active. Otherwise, use DP as clock source
	 * first, loop to find any HDMI audio, if not, loop find DP audio
	 */
	/* Setup audio rate clock source */
	/* Issue:
	* Audio lag happened on DP monitor when unplug a HDMI monitor
	*
	* Cause:
	* In case of DP and HDMI connected or HDMI only, DCCG_AUDIO_DTO_SEL
	* is set to either dto0 or dto1, audio should work fine.
	* In case of DP connected only, DCCG_AUDIO_DTO_SEL should be dto1,
	* set to dto0 will cause audio lag.
	*
	* Solution:
	* Not optimized audio wall dto setup. When mode set, iterate pipe_ctx,
	* find first available pipe with audio, setup audio wall DTO per topology
	* instead of per pipe.
	*/
	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		if (pipe_ctx->stream == NULL)
			continue;

		if (pipe_ctx->top_pipe)
			continue;

		if (pipe_ctx->stream->signal != SIGNAL_TYPE_HDMI_TYPE_A)
			continue;

		if (pipe_ctx->stream_res.audio != NULL) {
			struct audio_output audio_output;

			build_audio_output(context, pipe_ctx, &audio_output);

			pipe_ctx->stream_res.audio->funcs->wall_dto_setup(
				pipe_ctx->stream_res.audio,
				pipe_ctx->stream->signal,
				&audio_output.crtc_info,
				&audio_output.pll_info);
			break;
		}
	}

	/* no HDMI audio is found, try DP audio */
	if (i == dc->res_pool->pipe_count) {
		for (i = 0; i < dc->res_pool->pipe_count; i++) {
			struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

			if (pipe_ctx->stream == NULL)
				continue;

			if (pipe_ctx->top_pipe)
				continue;

			if (!dc_is_dp_signal(pipe_ctx->stream->signal))
				continue;

			if (pipe_ctx->stream_res.audio != NULL) {
				struct audio_output audio_output;

				build_audio_output(context, pipe_ctx, &audio_output);

				pipe_ctx->stream_res.audio->funcs->wall_dto_setup(
					pipe_ctx->stream_res.audio,
					pipe_ctx->stream->signal,
					&audio_output.crtc_info,
					&audio_output.pll_info);
				break;
			}
		}
	}
}