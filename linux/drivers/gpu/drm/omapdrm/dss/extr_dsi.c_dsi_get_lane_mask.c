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
struct dsi_data {int num_lanes_supported; TYPE_1__* lanes; } ;
struct TYPE_2__ {scalar_t__ function; } ;

/* Variables and functions */
 scalar_t__ DSI_LANE_UNUSED ; 

__attribute__((used)) static unsigned int dsi_get_lane_mask(struct dsi_data *dsi)
{
	unsigned int mask = 0;
	int i;

	for (i = 0; i < dsi->num_lanes_supported; ++i) {
		if (dsi->lanes[i].function != DSI_LANE_UNUSED)
			mask |= 1 << i;
	}

	return mask;
}