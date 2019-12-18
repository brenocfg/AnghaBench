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
typedef  int uint32_t ;
struct timing_generator {TYPE_5__* funcs; } ;
struct TYPE_19__ {TYPE_9__* stream_enc; int /*<<< orphan*/ * audio; struct timing_generator* tg; } ;
struct pipe_ctx {TYPE_8__ stream_res; TYPE_6__* stream; } ;
struct TYPE_12__ {int lane_count; } ;
struct dc_link {TYPE_4__* dc; TYPE_10__* link_enc; TYPE_1__ cur_link_settings; } ;
struct dc_crtc_timing {int h_addressable; int h_border_left; int h_border_right; } ;
typedef  enum dc_lane_count { ____Placeholder_dc_lane_count } dc_lane_count ;
struct TYPE_20__ {TYPE_7__* funcs; int /*<<< orphan*/  id; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* dp_audio_enable ) (TYPE_9__*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  signal; struct dc_link* link; struct dc_crtc_timing timing; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* set_early_control ) (struct timing_generator*,int) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* update_info_frame ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* program_dmdata_engine ) (struct pipe_ctx*) ;} ;
struct TYPE_15__ {TYPE_3__ hwss; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* connect_dig_be_to_fe ) (TYPE_10__*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_11__ {TYPE_2__* funcs; } ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub3 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub4 (struct timing_generator*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_9__*) ; 

__attribute__((used)) static void dcn20_enable_stream(struct pipe_ctx *pipe_ctx)
{
	enum dc_lane_count lane_count =
		pipe_ctx->stream->link->cur_link_settings.lane_count;

	struct dc_crtc_timing *timing = &pipe_ctx->stream->timing;
	struct dc_link *link = pipe_ctx->stream->link;

	uint32_t active_total_with_borders;
	uint32_t early_control = 0;
	struct timing_generator *tg = pipe_ctx->stream_res.tg;

	/* For MST, there are multiply stream go to only one link.
	 * connect DIG back_end to front_end while enable_stream and
	 * disconnect them during disable_stream
	 * BY this, it is logic clean to separate stream and link
	 */
	link->link_enc->funcs->connect_dig_be_to_fe(link->link_enc,
						    pipe_ctx->stream_res.stream_enc->id, true);

	if (link->dc->hwss.program_dmdata_engine)
		link->dc->hwss.program_dmdata_engine(pipe_ctx);

	link->dc->hwss.update_info_frame(pipe_ctx);

	/* enable early control to avoid corruption on DP monitor*/
	active_total_with_borders =
			timing->h_addressable
				+ timing->h_border_left
				+ timing->h_border_right;

	if (lane_count != 0)
		early_control = active_total_with_borders % lane_count;

	if (early_control == 0)
		early_control = lane_count;

	tg->funcs->set_early_control(tg, early_control);

	/* enable audio only within mode set */
	if (pipe_ctx->stream_res.audio != NULL) {
		if (dc_is_dp_signal(pipe_ctx->stream->signal))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_enable(pipe_ctx->stream_res.stream_enc);
	}
}