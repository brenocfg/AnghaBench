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
struct dc_link_settings {int member_3; scalar_t__ link_rate; scalar_t__ lane_count; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ link_rate; scalar_t__ lane_count; } ;
struct dc_link {TYPE_1__ verified_link_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LANE_COUNT_ONE ; 
 int /*<<< orphan*/  LINK_RATE_LOW ; 
 int /*<<< orphan*/  LINK_SPREAD_DISABLED ; 
 scalar_t__ dc_link_bandwidth_kbps (struct dc_link*,struct dc_link_settings*) ; 
 scalar_t__ increase_lane_count (scalar_t__) ; 
 scalar_t__ increase_link_rate (scalar_t__) ; 

__attribute__((used)) static bool decide_dp_link_settings(struct dc_link *link, struct dc_link_settings *link_setting, uint32_t req_bw)
{
	struct dc_link_settings initial_link_setting = {
		LANE_COUNT_ONE, LINK_RATE_LOW, LINK_SPREAD_DISABLED, false, 0};
	struct dc_link_settings current_link_setting =
			initial_link_setting;
	uint32_t link_bw;

	/* search for the minimum link setting that:
	 * 1. is supported according to the link training result
	 * 2. could support the b/w requested by the timing
	 */
	while (current_link_setting.link_rate <=
			link->verified_link_cap.link_rate) {
		link_bw = dc_link_bandwidth_kbps(
				link,
				&current_link_setting);
		if (req_bw <= link_bw) {
			*link_setting = current_link_setting;
			return true;
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

	return false;
}