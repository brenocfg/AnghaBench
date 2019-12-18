#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct dc_stream_state {scalar_t__ dpms_off; struct dc_link* link; } ;
struct dc_link_settings {scalar_t__ lane_count; scalar_t__ link_rate; } ;
struct dc_link {scalar_t__ dongle_max_pix_clk; int /*<<< orphan*/  connector_signal; struct dc_link_settings preferred_link_setting; } ;
struct dc {TYPE_2__* current_state; } ;
struct TYPE_3__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_4__ {TYPE_1__ res_ctx; } ;

/* Variables and functions */
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decide_link_settings (struct dc_stream_state*,struct dc_link_settings*) ; 
 int /*<<< orphan*/  dp_retrain_link_dp_test (struct dc_link*,struct dc_link_settings*,int) ; 

void dc_link_set_preferred_link_settings(struct dc *dc,
					 struct dc_link_settings *link_setting,
					 struct dc_link *link)
{
	int i;
	struct pipe_ctx *pipe;
	struct dc_stream_state *link_stream;
	struct dc_link_settings store_settings = *link_setting;

	link->preferred_link_setting = store_settings;

	/* Retrain with preferred link settings only relevant for
	 * DP signal type
	 * Check for non-DP signal or if passive dongle present
	 */
	if (!dc_is_dp_signal(link->connector_signal) ||
		link->dongle_max_pix_clk > 0)
		return;

	for (i = 0; i < MAX_PIPES; i++) {
		pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		if (pipe->stream && pipe->stream->link) {
			if (pipe->stream->link == link) {
				link_stream = pipe->stream;
				break;
			}
		}
	}

	/* Stream not found */
	if (i == MAX_PIPES)
		return;

	/* Cannot retrain link if backend is off */
	if (link_stream->dpms_off)
		return;

	decide_link_settings(link_stream, &store_settings);

	if ((store_settings.lane_count != LANE_COUNT_UNKNOWN) &&
		(store_settings.link_rate != LINK_RATE_UNKNOWN))
		dp_retrain_link_dp_test(link, &store_settings, false);
}