#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_12__* stream_enc; TYPE_13__* audio; } ;
struct pipe_ctx {TYPE_11__ stream_res; TYPE_6__* clock_source; TYPE_4__* stream; int /*<<< orphan*/  top_pipe; } ;
struct dc_link_settings {int dummy; } ;
struct dc_link {TYPE_8__* dc; struct dc_link_settings cur_link_settings; TYPE_14__* link_enc; } ;
struct TYPE_30__ {int /*<<< orphan*/  (* az_enable ) (TYPE_13__*) ;} ;
struct TYPE_28__ {int /*<<< orphan*/  (* unblank_stream ) (struct pipe_ctx*,struct dc_link_settings*) ;int /*<<< orphan*/  (* enable_stream ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* disable_stream ) (struct pipe_ctx*,int /*<<< orphan*/ ) ;} ;
struct TYPE_29__ {TYPE_7__ hwss; TYPE_2__* current_state; } ;
struct TYPE_27__ {int /*<<< orphan*/  id; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* enable_dp_output ) (TYPE_14__*,struct dc_link_settings*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_output ) (TYPE_14__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_25__ {TYPE_3__* sink; } ;
struct TYPE_24__ {struct dc_link* link; } ;
struct TYPE_22__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_23__ {TYPE_1__ res_ctx; } ;
struct TYPE_21__ {TYPE_5__* funcs; } ;
struct TYPE_20__ {TYPE_9__* funcs; } ;
struct TYPE_19__ {TYPE_10__* funcs; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* audio_mute_control ) (TYPE_12__*,int) ;int /*<<< orphan*/  (* dp_blank ) (TYPE_12__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TEST_PATTERN_VIDEO_MODE ; 
 int /*<<< orphan*/  KEEP_ACQUIRED_RESOURCE ; 
 int /*<<< orphan*/  LINK_TRAINING_ATTEMPTS ; 
 unsigned int MAX_PIPES ; 
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  dp_receiver_power_ctrl (struct dc_link*,int) ; 
 int /*<<< orphan*/  dp_set_hw_test_pattern (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dc_link_settings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perform_link_training_with_retries (struct dc_link*,struct dc_link_settings*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_12__*) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_14__*,struct dc_link_settings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub6 (struct pipe_ctx*,struct dc_link_settings*) ; 
 int /*<<< orphan*/  stub7 (TYPE_13__*) ; 
 int /*<<< orphan*/  stub8 (TYPE_12__*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void dp_retrain_link_dp_test(struct dc_link *link,
			struct dc_link_settings *link_setting,
			bool skip_video_pattern)
{
	struct pipe_ctx *pipes =
			&link->dc->current_state->res_ctx.pipe_ctx[0];
	unsigned int i;

	for (i = 0; i < MAX_PIPES; i++) {
		if (pipes[i].stream != NULL &&
			!pipes[i].top_pipe &&
			pipes[i].stream->sink != NULL &&
			pipes[i].stream->sink->link != NULL &&
			pipes[i].stream_res.stream_enc != NULL &&
			pipes[i].stream->sink->link == link) {
			udelay(100);

			pipes[i].stream_res.stream_enc->funcs->dp_blank(
					pipes[i].stream_res.stream_enc);

			/* disable any test pattern that might be active */
			dp_set_hw_test_pattern(link,
					DP_TEST_PATTERN_VIDEO_MODE, NULL, 0);

			dp_receiver_power_ctrl(link, false);

			link->dc->hwss.disable_stream(&pipes[i], KEEP_ACQUIRED_RESOURCE);

			link->link_enc->funcs->disable_output(
					link->link_enc,
					SIGNAL_TYPE_DISPLAY_PORT);

			/* Clear current link setting. */
			memset(&link->cur_link_settings, 0,
				sizeof(link->cur_link_settings));

			link->link_enc->funcs->enable_dp_output(
						link->link_enc,
						link_setting,
						pipes[i].clock_source->id);

			dp_receiver_power_ctrl(link, true);

			perform_link_training_with_retries(
					link,
					link_setting,
					skip_video_pattern,
					LINK_TRAINING_ATTEMPTS);

			link->cur_link_settings = *link_setting;

			link->dc->hwss.enable_stream(&pipes[i]);

			link->dc->hwss.unblank_stream(&pipes[i],
					link_setting);

			if (pipes[i].stream_res.audio) {
				/* notify audio driver for
				 * audio modes of monitor */
				pipes[i].stream_res.audio->funcs->az_enable(
						pipes[i].stream_res.audio);

				/* un-mute audio */
				/* TODO: audio should be per stream rather than
				 * per link */
				pipes[i].stream_res.stream_enc->funcs->
				audio_mute_control(
					pipes[i].stream_res.stream_enc, false);
			}
		}
	}
}