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
struct TYPE_12__ {int /*<<< orphan*/  ss_percentage; int /*<<< orphan*/  feedback_divider; } ;
struct TYPE_18__ {int requested_pix_clk_100hz; scalar_t__ pixel_encoding; } ;
struct TYPE_21__ {TYPE_7__* tg; TYPE_5__ pix_clk_params; TYPE_1__* stream_enc; } ;
struct pipe_ctx {TYPE_10__ pll_settings; TYPE_8__ stream_res; struct dc_stream_state* stream; } ;
struct TYPE_15__ {int /*<<< orphan*/  INTERLACE; } ;
struct TYPE_16__ {int h_total; int pix_clk_100hz; int v_total; int /*<<< orphan*/  display_color_depth; TYPE_2__ flags; scalar_t__ v_border_bottom; scalar_t__ v_border_top; scalar_t__ v_addressable; scalar_t__ h_border_right; scalar_t__ h_border_left; scalar_t__ h_addressable; } ;
struct dc_stream_state {scalar_t__ signal; TYPE_3__ timing; } ;
struct dc_state {TYPE_11__* clk_mgr; } ;
struct TYPE_22__ {int ss_enabled; int /*<<< orphan*/  ss_percentage; int /*<<< orphan*/  dto_source; int /*<<< orphan*/  feed_back_divider; int /*<<< orphan*/  dp_dto_source_clock_in_khz; } ;
struct TYPE_17__ {int h_total; int pixel_repetition; int refresh_rate; int requested_pixel_clock_100Hz; int calculated_pixel_clock_100Hz; int /*<<< orphan*/  color_depth; int /*<<< orphan*/  interlaced; scalar_t__ v_active; scalar_t__ h_active; } ;
struct audio_output {scalar_t__ signal; TYPE_9__ pll_info; TYPE_4__ crtc_info; int /*<<< orphan*/  engine_id; } ;
struct TYPE_20__ {scalar_t__ inst; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* get_dp_ref_clk_frequency ) (TYPE_11__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_6__* funcs; } ;

/* Variables and functions */
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ dc_is_hdmi_signal (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*) ; 
 int /*<<< orphan*/  translate_to_dto_source (scalar_t__) ; 

__attribute__((used)) static void build_audio_output(
	struct dc_state *state,
	const struct pipe_ctx *pipe_ctx,
	struct audio_output *audio_output)
{
	const struct dc_stream_state *stream = pipe_ctx->stream;
	audio_output->engine_id = pipe_ctx->stream_res.stream_enc->id;

	audio_output->signal = pipe_ctx->stream->signal;

	/* audio_crtc_info  */

	audio_output->crtc_info.h_total =
		stream->timing.h_total;

	/*
	 * Audio packets are sent during actual CRTC blank physical signal, we
	 * need to specify actual active signal portion
	 */
	audio_output->crtc_info.h_active =
			stream->timing.h_addressable
			+ stream->timing.h_border_left
			+ stream->timing.h_border_right;

	audio_output->crtc_info.v_active =
			stream->timing.v_addressable
			+ stream->timing.v_border_top
			+ stream->timing.v_border_bottom;

	audio_output->crtc_info.pixel_repetition = 1;

	audio_output->crtc_info.interlaced =
			stream->timing.flags.INTERLACE;

	audio_output->crtc_info.refresh_rate =
		(stream->timing.pix_clk_100hz*100)/
		(stream->timing.h_total*stream->timing.v_total);

	audio_output->crtc_info.color_depth =
		stream->timing.display_color_depth;

	audio_output->crtc_info.requested_pixel_clock_100Hz =
			pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz;

	audio_output->crtc_info.calculated_pixel_clock_100Hz =
			pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz;

/*for HDMI, audio ACR is with deep color ratio factor*/
	if (dc_is_hdmi_signal(pipe_ctx->stream->signal) &&
		audio_output->crtc_info.requested_pixel_clock_100Hz ==
				(stream->timing.pix_clk_100hz)) {
		if (pipe_ctx->stream_res.pix_clk_params.pixel_encoding == PIXEL_ENCODING_YCBCR420) {
			audio_output->crtc_info.requested_pixel_clock_100Hz =
					audio_output->crtc_info.requested_pixel_clock_100Hz/2;
			audio_output->crtc_info.calculated_pixel_clock_100Hz =
					pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz/2;

		}
	}

	if (pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT ||
			pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST) {
		audio_output->pll_info.dp_dto_source_clock_in_khz =
				state->clk_mgr->funcs->get_dp_ref_clk_frequency(
						state->clk_mgr);
	}

	audio_output->pll_info.feed_back_divider =
			pipe_ctx->pll_settings.feedback_divider;

	audio_output->pll_info.dto_source =
		translate_to_dto_source(
			pipe_ctx->stream_res.tg->inst + 1);

	/* TODO hard code to enable for now. Need get from stream */
	audio_output->pll_info.ss_enabled = true;

	audio_output->pll_info.ss_percentage =
			pipe_ctx->pll_settings.ss_percentage;
}