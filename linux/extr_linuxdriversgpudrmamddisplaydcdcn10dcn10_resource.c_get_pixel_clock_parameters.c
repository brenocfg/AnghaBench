#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int DISPLAY_BLANKED; scalar_t__ ENABLE_SS; } ;
struct pixel_clk_params {int requested_pix_clk; int requested_sym_clk; scalar_t__ pixel_encoding; int /*<<< orphan*/  color_depth; TYPE_6__ flags; scalar_t__ controller_id; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  encoder_object_id; } ;
struct TYPE_12__ {TYPE_4__* tg; } ;
struct pipe_ctx {TYPE_5__ stream_res; struct dc_stream_state* stream; } ;
struct TYPE_14__ {int pix_clk_khz; scalar_t__ pixel_encoding; int /*<<< orphan*/  display_color_depth; } ;
struct dc_stream_state {TYPE_7__ timing; int /*<<< orphan*/  signal; TYPE_3__* sink; } ;
struct TYPE_11__ {scalar_t__ inst; } ;
struct TYPE_10__ {TYPE_2__* link; } ;
struct TYPE_9__ {TYPE_1__* link_enc; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_DEPTH_888 ; 
 int LINK_RATE_LOW ; 
 int LINK_RATE_REF_FREQ_IN_KHZ ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ PIXEL_ENCODING_YCBCR422 ; 

__attribute__((used)) static void get_pixel_clock_parameters(
	const struct pipe_ctx *pipe_ctx,
	struct pixel_clk_params *pixel_clk_params)
{
	const struct dc_stream_state *stream = pipe_ctx->stream;
	pixel_clk_params->requested_pix_clk = stream->timing.pix_clk_khz;
	pixel_clk_params->encoder_object_id = stream->sink->link->link_enc->id;
	pixel_clk_params->signal_type = pipe_ctx->stream->signal;
	pixel_clk_params->controller_id = pipe_ctx->stream_res.tg->inst + 1;
	/* TODO: un-hardcode*/
	pixel_clk_params->requested_sym_clk = LINK_RATE_LOW *
		LINK_RATE_REF_FREQ_IN_KHZ;
	pixel_clk_params->flags.ENABLE_SS = 0;
	pixel_clk_params->color_depth =
		stream->timing.display_color_depth;
	pixel_clk_params->flags.DISPLAY_BLANKED = 1;
	pixel_clk_params->pixel_encoding = stream->timing.pixel_encoding;

	if (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
		pixel_clk_params->color_depth = COLOR_DEPTH_888;

	if (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
		pixel_clk_params->requested_pix_clk  /= 2;

}