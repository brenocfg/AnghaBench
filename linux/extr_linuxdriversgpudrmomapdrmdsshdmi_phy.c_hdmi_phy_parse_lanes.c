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
typedef  size_t u8 ;
typedef  int u32 ;
struct hdmi_phy_data {int* lane_function; size_t* lane_polarity; } ;

/* Variables and functions */
 int EINVAL ; 

int hdmi_phy_parse_lanes(struct hdmi_phy_data *phy, const u32 *lanes)
{
	int i;

	for (i = 0; i < 8; i += 2) {
		u8 lane, pol;
		int dx, dy;

		dx = lanes[i];
		dy = lanes[i + 1];

		if (dx < 0 || dx >= 8)
			return -EINVAL;

		if (dy < 0 || dy >= 8)
			return -EINVAL;

		if (dx & 1) {
			if (dy != dx - 1)
				return -EINVAL;
			pol = 1;
		} else {
			if (dy != dx + 1)
				return -EINVAL;
			pol = 0;
		}

		lane = dx / 2;

		phy->lane_function[lane] = i / 2;
		phy->lane_polarity[lane] = pol;
	}

	return 0;
}