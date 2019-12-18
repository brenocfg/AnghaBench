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
struct dc_link_settings {scalar_t__ lane_count; scalar_t__ link_rate; } ;
struct dc_link {struct dc_link_settings const verified_link_cap; struct dc_link_settings const preferred_link_setting; } ;

/* Variables and functions */
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 

const struct dc_link_settings *dc_link_get_link_cap(
		const struct dc_link *link)
{
	if (link->preferred_link_setting.lane_count != LANE_COUNT_UNKNOWN &&
			link->preferred_link_setting.link_rate != LINK_RATE_UNKNOWN)
		return &link->preferred_link_setting;
	return &link->verified_link_cap;
}