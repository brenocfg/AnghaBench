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
struct TYPE_2__ {int data_lane0_reg1; } ;
struct mipid02_dev {TYPE_1__ r; } ;

/* Variables and functions */
 int DATA_ENABLE ; 

__attribute__((used)) static int mipid02_configure_data0_lane(struct mipid02_dev *bridge, int nb,
					bool are_lanes_swap, bool *polarities)
{
	bool are_pin_swap = are_lanes_swap ? polarities[2] : polarities[1];

	if (nb == 1 && are_lanes_swap)
		return 0;

	/*
	 * data lane 0 as pin swap polarity reversed compared to clock and
	 * data lane 1
	 */
	if (!are_pin_swap)
		bridge->r.data_lane0_reg1 = 1 << 1;
	bridge->r.data_lane0_reg1 |= DATA_ENABLE;

	return 0;
}