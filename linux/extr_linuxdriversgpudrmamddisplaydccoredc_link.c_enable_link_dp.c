#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct pipe_ctx {TYPE_8__* clock_source; struct dc_stream_state* stream; } ;
struct dc_stream_state {TYPE_11__* sink; int /*<<< orphan*/  signal; } ;
struct dc_clocks {int phyclk_khz; scalar_t__ dispclk_khz; } ;
struct TYPE_20__ {struct dc_clocks clk; } ;
struct TYPE_21__ {TYPE_5__ dcn; } ;
struct dc_state {TYPE_12__* dis_clk; TYPE_6__ bw; } ;
struct dc_link_settings {int link_rate; int /*<<< orphan*/  member_0; } ;
struct dc_link {struct dc_link_settings cur_link_settings; TYPE_4__* link_enc; } ;
typedef  enum dp_panel_mode { ____Placeholder_dp_panel_mode } dp_panel_mode ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
typedef  enum dc_link_rate { ____Placeholder_dc_link_rate } dc_link_rate ;
struct TYPE_24__ {int dppowerup_delay; } ;
struct TYPE_23__ {int /*<<< orphan*/  id; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* update_clocks ) (TYPE_12__*,struct dc_clocks*,int) ;} ;
struct TYPE_16__ {scalar_t__ IS_HBR3_CAPABLE; } ;
struct TYPE_17__ {TYPE_1__ bits; } ;
struct TYPE_18__ {TYPE_2__ flags; } ;
struct TYPE_19__ {TYPE_3__ features; } ;
struct TYPE_15__ {TYPE_7__* funcs; } ;
struct TYPE_13__ {TYPE_9__ panel_patch; } ;
struct TYPE_14__ {TYPE_10__ edid_caps; struct dc_link* link; } ;

/* Variables and functions */
 int DC_FAIL_DP_LINK_TRAINING ; 
 int DC_OK ; 
 int LINK_RATE_HIGH2 ; 
 int LINK_RATE_HIGH3 ; 
 int LINK_RATE_LOW ; 
 int /*<<< orphan*/  LINK_TRAINING_ATTEMPTS ; 
 int /*<<< orphan*/  decide_link_settings (struct dc_stream_state*,struct dc_link_settings*) ; 
 int /*<<< orphan*/  dp_enable_link_phy (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dc_link_settings*) ; 
 int dp_get_panel_mode (struct dc_link*) ; 
 int /*<<< orphan*/  dpcd_configure_panel_mode (struct dc_link*,int) ; 
 int /*<<< orphan*/  enable_stream_features (struct pipe_ctx*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ perform_link_training_with_retries (struct dc_link*,struct dc_link_settings*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_12__*,struct dc_clocks*,int) ; 

__attribute__((used)) static enum dc_status enable_link_dp(
		struct dc_state *state,
		struct pipe_ctx *pipe_ctx)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	enum dc_status status;
	bool skip_video_pattern;
	struct dc_link *link = stream->sink->link;
	struct dc_link_settings link_settings = {0};
	enum dp_panel_mode panel_mode;
	enum dc_link_rate max_link_rate = LINK_RATE_HIGH2;

	/* get link settings for video mode timing */
	decide_link_settings(stream, &link_settings);

	/* raise clock state for HBR3 if required. Confirmed with HW DCE/DPCS
	 * logic for HBR3 still needs Nominal (0.8V) on VDDC rail
	 */
	if (link->link_enc->features.flags.bits.IS_HBR3_CAPABLE)
		max_link_rate = LINK_RATE_HIGH3;

	if (link_settings.link_rate == max_link_rate) {
		struct dc_clocks clocks = state->bw.dcn.clk;

		/* dce/dcn compat, do not update dispclk */
		clocks.dispclk_khz = 0;
		/* 27mhz = 27000000hz= 27000khz */
		clocks.phyclk_khz = link_settings.link_rate * 27000;

		state->dis_clk->funcs->update_clocks(
				state->dis_clk, &clocks, false);
	}

	dp_enable_link_phy(
		link,
		pipe_ctx->stream->signal,
		pipe_ctx->clock_source->id,
		&link_settings);

	if (stream->sink->edid_caps.panel_patch.dppowerup_delay > 0) {
		int delay_dp_power_up_in_ms = stream->sink->edid_caps.panel_patch.dppowerup_delay;

		msleep(delay_dp_power_up_in_ms);
	}

	panel_mode = dp_get_panel_mode(link);
	dpcd_configure_panel_mode(link, panel_mode);

	skip_video_pattern = true;

	if (link_settings.link_rate == LINK_RATE_LOW)
			skip_video_pattern = false;

	if (perform_link_training_with_retries(
			link,
			&link_settings,
			skip_video_pattern,
			LINK_TRAINING_ATTEMPTS)) {
		link->cur_link_settings = link_settings;
		status = DC_OK;
	}
	else
		status = DC_FAIL_DP_LINK_TRAINING;

	enable_stream_features(pipe_ctx);

	return status;
}