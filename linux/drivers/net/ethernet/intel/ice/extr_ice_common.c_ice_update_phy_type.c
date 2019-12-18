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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int ICE_PHY_TYPE_HIGH_MAX_INDEX ; 
 int ICE_PHY_TYPE_LOW_MAX_INDEX ; 
 int ice_get_link_speed_based_on_phy_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ice_update_phy_type(u64 *phy_type_low, u64 *phy_type_high,
		    u16 link_speeds_bitmap)
{
	u64 pt_high;
	u64 pt_low;
	int index;
	u16 speed;

	/* We first check with low part of phy_type */
	for (index = 0; index <= ICE_PHY_TYPE_LOW_MAX_INDEX; index++) {
		pt_low = BIT_ULL(index);
		speed = ice_get_link_speed_based_on_phy_type(pt_low, 0);

		if (link_speeds_bitmap & speed)
			*phy_type_low |= BIT_ULL(index);
	}

	/* We then check with high part of phy_type */
	for (index = 0; index <= ICE_PHY_TYPE_HIGH_MAX_INDEX; index++) {
		pt_high = BIT_ULL(index);
		speed = ice_get_link_speed_based_on_phy_type(0, pt_high);

		if (link_speeds_bitmap & speed)
			*phy_type_high |= BIT_ULL(index);
	}
}