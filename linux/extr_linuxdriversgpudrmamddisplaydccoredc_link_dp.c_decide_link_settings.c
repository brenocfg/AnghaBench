#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dc_stream_state {scalar_t__ signal; TYPE_1__* sink; int /*<<< orphan*/  timing; } ;
struct dc_link_settings {scalar_t__ lane_count; scalar_t__ link_rate; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dc_link {struct dc_link_settings verified_link_cap; struct dc_link_settings preferred_link_setting; } ;
struct TYPE_2__ {scalar_t__ sink_signal; struct dc_link* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  LANE_COUNT_ONE ; 
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 int /*<<< orphan*/  LINK_RATE_LOW ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  LINK_SPREAD_DISABLED ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ SIGNAL_TYPE_EDP ; 
 scalar_t__ bandwidth_in_kbps_from_link_settings (struct dc_link_settings*) ; 
 scalar_t__ bandwidth_in_kbps_from_timing (int /*<<< orphan*/ *) ; 
 scalar_t__ increase_lane_count (scalar_t__) ; 
 scalar_t__ increase_link_rate (scalar_t__) ; 

void decide_link_settings(struct dc_stream_state *stream,
	struct dc_link_settings *link_setting)
{

	struct dc_link_settings initial_link_setting = {
		LANE_COUNT_ONE, LINK_RATE_LOW, LINK_SPREAD_DISABLED};
	struct dc_link_settings current_link_setting =
			initial_link_setting;
	struct dc_link *link;
	uint32_t req_bw;
	uint32_t link_bw;

	req_bw = bandwidth_in_kbps_from_timing(&stream->timing);

	link = stream->sink->link;

	/* if preferred is specified through AMDDP, use it, if it's enough
	 * to drive the mode
	 */
	if (link->preferred_link_setting.lane_count !=
			LANE_COUNT_UNKNOWN &&
			link->preferred_link_setting.link_rate !=
					LINK_RATE_UNKNOWN) {
		*link_setting =  link->preferred_link_setting;
		return;
	}

	/* MST doesn't perform link training for now
	 * TODO: add MST specific link training routine
	 */
	if (stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST) {
		*link_setting = link->verified_link_cap;
		return;
	}

	/* EDP use the link cap setting */
	if (stream->sink->sink_signal == SIGNAL_TYPE_EDP) {
		*link_setting = link->verified_link_cap;
		return;
	}

	/* search for the minimum link setting that:
	 * 1. is supported according to the link training result
	 * 2. could support the b/w requested by the timing
	 */
	while (current_link_setting.link_rate <=
			link->verified_link_cap.link_rate) {
		link_bw = bandwidth_in_kbps_from_link_settings(
				&current_link_setting);
		if (req_bw <= link_bw) {
			*link_setting = current_link_setting;
			return;
		}

		if (current_link_setting.lane_count <
				link->verified_link_cap.lane_count) {
			current_link_setting.lane_count =
					increase_lane_count(
							current_link_setting.lane_count);
		} else {
			current_link_setting.link_rate =
					increase_link_rate(
							current_link_setting.link_rate);
			current_link_setting.lane_count =
					initial_link_setting.lane_count;
		}
	}

	BREAK_TO_DEBUGGER();
	ASSERT(link->verified_link_cap.lane_count != LANE_COUNT_UNKNOWN);

	*link_setting = link->verified_link_cap;
}