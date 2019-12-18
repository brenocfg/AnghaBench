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
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t lane_count; } ;
struct link_training_settings {int /*<<< orphan*/ * post_cursor2; TYPE_2__* lane_settings; int /*<<< orphan*/ * pre_emphasis; int /*<<< orphan*/ * voltage_swing; TYPE_1__ link_settings; } ;
struct TYPE_4__ {int /*<<< orphan*/  POST_CURSOR2; int /*<<< orphan*/  PRE_EMPHASIS; int /*<<< orphan*/  VOLTAGE_SWING; } ;

/* Variables and functions */

__attribute__((used)) static void update_drive_settings(
		struct link_training_settings *dest,
		struct link_training_settings src)
{
	uint32_t lane;
	for (lane = 0; lane < src.link_settings.lane_count; lane++) {
		if (dest->voltage_swing == NULL)
			dest->lane_settings[lane].VOLTAGE_SWING = src.lane_settings[lane].VOLTAGE_SWING;
		else
			dest->lane_settings[lane].VOLTAGE_SWING = *dest->voltage_swing;

		if (dest->pre_emphasis == NULL)
			dest->lane_settings[lane].PRE_EMPHASIS = src.lane_settings[lane].PRE_EMPHASIS;
		else
			dest->lane_settings[lane].PRE_EMPHASIS = *dest->pre_emphasis;

		if (dest->post_cursor2 == NULL)
			dest->lane_settings[lane].POST_CURSOR2 = src.lane_settings[lane].POST_CURSOR2;
		else
			dest->lane_settings[lane].POST_CURSOR2 = *dest->post_cursor2;
	}
}