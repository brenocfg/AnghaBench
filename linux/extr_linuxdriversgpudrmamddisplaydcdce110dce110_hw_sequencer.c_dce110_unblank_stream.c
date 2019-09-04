#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_10__* stream_enc; } ;
struct pipe_ctx {TYPE_6__ stream_res; struct dc_stream_state* stream; } ;
struct TYPE_15__ {int /*<<< orphan*/  link_rate; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
struct encoder_unblank_param {TYPE_4__ link_settings; int /*<<< orphan*/  pixel_clk_khz; TYPE_1__ member_0; } ;
struct TYPE_14__ {int /*<<< orphan*/  pix_clk_khz; } ;
struct dc_stream_state {int /*<<< orphan*/  bl_pwm_level; int /*<<< orphan*/  signal; TYPE_3__ timing; TYPE_2__* sink; } ;
struct dc_link_settings {int /*<<< orphan*/  link_rate; } ;
struct dc_link {TYPE_9__* dc; TYPE_7__* local_sink; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* edp_backlight_control ) (struct dc_link*,int) ;} ;
struct TYPE_20__ {TYPE_8__ hwss; } ;
struct TYPE_18__ {scalar_t__ sink_signal; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* dp_unblank ) (TYPE_10__*,struct encoder_unblank_param*) ;} ;
struct TYPE_13__ {struct dc_link* link; } ;
struct TYPE_11__ {TYPE_5__* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_BACKLIGHT_RAMP_DISABLE_LEVEL ; 
 scalar_t__ SIGNAL_TYPE_EDP ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,struct encoder_unblank_param*) ; 
 int /*<<< orphan*/  stub2 (struct dc_link*,int) ; 

void dce110_unblank_stream(struct pipe_ctx *pipe_ctx,
		struct dc_link_settings *link_settings)
{
	struct encoder_unblank_param params = { { 0 } };
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->sink->link;

	/* only 3 items below are used by unblank */
	params.pixel_clk_khz =
		pipe_ctx->stream->timing.pix_clk_khz;
	params.link_settings.link_rate = link_settings->link_rate;

	if (dc_is_dp_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dp_unblank(pipe_ctx->stream_res.stream_enc, &params);

	if (link->local_sink && link->local_sink->sink_signal == SIGNAL_TYPE_EDP) {
		link->dc->hwss.edp_backlight_control(link, true);
		stream->bl_pwm_level = EDP_BACKLIGHT_RAMP_DISABLE_LEVEL;
	}
}