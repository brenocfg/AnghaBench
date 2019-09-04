#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_8__* tg; } ;
struct pipe_ctx {TYPE_7__* stream; TYPE_3__ stream_res; } ;
struct dc_state {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* unblank_stream ) (struct pipe_ctx*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* enable_stream ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* enable_audio_stream ) (struct pipe_ctx*) ;} ;
struct dc {int apply_edp_fast_boot_optimization; TYPE_4__ hwss; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_16__ {TYPE_2__* funcs; } ;
struct TYPE_15__ {scalar_t__ signal; int dpms_off; TYPE_6__* sink; TYPE_1__* ctx; } ;
struct TYPE_14__ {TYPE_5__* link; } ;
struct TYPE_13__ {int /*<<< orphan*/  cur_link_settings; int /*<<< orphan*/  link_index; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* set_test_pattern ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  logger; struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  COLOR_DEPTH_UNDEFINED ; 
 int /*<<< orphan*/  CONTROLLER_DP_TEST_PATTERN_VIDEOMODE ; 
 int DC_FAIL_DP_LINK_TRAINING ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*,int /*<<< orphan*/ ,int) ; 
 int DC_OK ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ SIGNAL_TYPE_EDP ; 
 int /*<<< orphan*/  allocate_mst_payload (struct pipe_ctx*) ; 
 int enable_link (struct dc_state*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub4 (struct pipe_ctx*,int /*<<< orphan*/ *) ; 

void core_link_enable_stream(
		struct dc_state *state,
		struct pipe_ctx *pipe_ctx)
{
	struct dc  *core_dc = pipe_ctx->stream->ctx->dc;
	enum dc_status status;
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);

	/* eDP lit up by bios already, no need to enable again. */
	if (pipe_ctx->stream->signal == SIGNAL_TYPE_EDP &&
		core_dc->apply_edp_fast_boot_optimization) {
		core_dc->apply_edp_fast_boot_optimization = false;
		pipe_ctx->stream->dpms_off = false;
		return;
	}

	if (pipe_ctx->stream->dpms_off)
		return;

	status = enable_link(state, pipe_ctx);

	if (status != DC_OK) {
			DC_LOG_WARNING("enabling link %u failed: %d\n",
			pipe_ctx->stream->sink->link->link_index,
			status);

			/* Abort stream enable *unless* the failure was due to
			 * DP link training - some DP monitors will recover and
			 * show the stream anyway. But MST displays can't proceed
			 * without link training.
			 */
			if (status != DC_FAIL_DP_LINK_TRAINING ||
					pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST) {
				BREAK_TO_DEBUGGER();
				return;
			}
	}

	core_dc->hwss.enable_audio_stream(pipe_ctx);

	/* turn off otg test pattern if enable */
	if (pipe_ctx->stream_res.tg->funcs->set_test_pattern)
		pipe_ctx->stream_res.tg->funcs->set_test_pattern(pipe_ctx->stream_res.tg,
				CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
				COLOR_DEPTH_UNDEFINED);

	core_dc->hwss.enable_stream(pipe_ctx);

	if (pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST)
		allocate_mst_payload(pipe_ctx);

	core_dc->hwss.unblank_stream(pipe_ctx,
		&pipe_ctx->stream->sink->link->cur_link_settings);
}