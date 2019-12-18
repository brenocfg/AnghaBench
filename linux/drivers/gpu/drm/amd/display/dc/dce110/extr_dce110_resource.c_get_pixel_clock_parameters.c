#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int DISPLAY_BLANKED; int SUPPORT_YCBCR420; scalar_t__ ENABLE_SS; } ;
struct pixel_clk_params {int requested_pix_clk_100hz; int requested_sym_clk; scalar_t__ pixel_encoding; int /*<<< orphan*/  color_depth; TYPE_5__ flags; scalar_t__ controller_id; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  encoder_object_id; } ;
struct TYPE_10__ {TYPE_3__* tg; } ;
struct pipe_ctx {TYPE_4__ stream_res; struct dc_stream_state* stream; } ;
struct TYPE_12__ {int pix_clk_100hz; scalar_t__ pixel_encoding; scalar_t__ timing_3d_format; int /*<<< orphan*/  display_color_depth; } ;
struct dc_stream_state {TYPE_6__ timing; int /*<<< orphan*/  signal; TYPE_2__* link; } ;
struct TYPE_9__ {scalar_t__ inst; } ;
struct TYPE_8__ {TYPE_1__* link_enc; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_DEPTH_888 ; 
 int LINK_RATE_LOW ; 
 int LINK_RATE_REF_FREQ_IN_KHZ ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 
 scalar_t__ TIMING_3D_FORMAT_HW_FRAME_PACKING ; 

__attribute__((used)) static void get_pixel_clock_parameters(
	const struct pipe_ctx *pipe_ctx,
	struct pixel_clk_params *pixel_clk_params)
{
	const struct dc_stream_state *stream = pipe_ctx->stream;

	/*TODO: is this halved for YCbCr 420? in that case we might want to move
	 * the pixel clock normalization for hdmi up to here instead of doing it
	 * in pll_adjust_pix_clk
	 */
	pixel_clk_params->requested_pix_clk_100hz = stream->timing.pix_clk_100hz;
	pixel_clk_params->encoder_object_id = stream->link->link_enc->id;
	pixel_clk_params->signal_type = pipe_ctx->stream->signal;
	pixel_clk_params->controller_id = pipe_ctx->stream_res.tg->inst + 1;
	/* TODO: un-hardcode*/
	pixel_clk_params->requested_sym_clk = LINK_RATE_LOW *
						LINK_RATE_REF_FREQ_IN_KHZ;
	pixel_clk_params->flags.ENABLE_SS = 0;
	pixel_clk_params->color_depth =
		stream->timing.display_color_depth;
	pixel_clk_params->flags.DISPLAY_BLANKED = 1;
	pixel_clk_params->flags.SUPPORT_YCBCR420 = (stream->timing.pixel_encoding ==
			PIXEL_ENCODING_YCBCR420);
	pixel_clk_params->pixel_encoding = stream->timing.pixel_encoding;
	if (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR422) {
		pixel_clk_params->color_depth = COLOR_DEPTH_888;
	}
	if (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420) {
		pixel_clk_params->requested_pix_clk_100hz  = pixel_clk_params->requested_pix_clk_100hz / 2;
	}
	if (stream->timing.timing_3d_format == TIMING_3D_FORMAT_HW_FRAME_PACKING)
		pixel_clk_params->requested_pix_clk_100hz *= 2;

}