#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dc_link_settings {scalar_t__ lane_count; scalar_t__ link_rate; int /*<<< orphan*/  link_spread; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ LINK_RATE_HIGH ; 
 scalar_t__ LINK_RATE_HIGH2 ; 
 scalar_t__ LINK_RATE_HIGH3 ; 
 scalar_t__ LINK_RATE_LOW ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  LINK_SPREAD_DISABLED ; 

__attribute__((used)) static struct dc_link_settings get_common_supported_link_settings(
		struct dc_link_settings link_setting_a,
		struct dc_link_settings link_setting_b)
{
	struct dc_link_settings link_settings = {0};

	link_settings.lane_count =
		(link_setting_a.lane_count <=
			link_setting_b.lane_count) ?
			link_setting_a.lane_count :
			link_setting_b.lane_count;
	link_settings.link_rate =
		(link_setting_a.link_rate <=
			link_setting_b.link_rate) ?
			link_setting_a.link_rate :
			link_setting_b.link_rate;
	link_settings.link_spread = LINK_SPREAD_DISABLED;

	/* in DP compliance test, DPR-120 may have
	 * a random value in its MAX_LINK_BW dpcd field.
	 * We map it to the maximum supported link rate that
	 * is smaller than MAX_LINK_BW in this case.
	 */
	if (link_settings.link_rate > LINK_RATE_HIGH3) {
		link_settings.link_rate = LINK_RATE_HIGH3;
	} else if (link_settings.link_rate < LINK_RATE_HIGH3
			&& link_settings.link_rate > LINK_RATE_HIGH2) {
		link_settings.link_rate = LINK_RATE_HIGH2;
	} else if (link_settings.link_rate < LINK_RATE_HIGH2
			&& link_settings.link_rate > LINK_RATE_HIGH) {
		link_settings.link_rate = LINK_RATE_HIGH;
	} else if (link_settings.link_rate < LINK_RATE_HIGH
			&& link_settings.link_rate > LINK_RATE_LOW) {
		link_settings.link_rate = LINK_RATE_LOW;
	} else if (link_settings.link_rate < LINK_RATE_LOW) {
		link_settings.link_rate = LINK_RATE_UNKNOWN;
	}

	return link_settings;
}