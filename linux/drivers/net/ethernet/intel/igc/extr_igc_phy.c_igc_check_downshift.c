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
struct igc_phy_info {int type; int speed_downgraded; } ;
struct igc_hw {struct igc_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  igc_phy_i225 128 

s32 igc_check_downshift(struct igc_hw *hw)
{
	struct igc_phy_info *phy = &hw->phy;
	s32 ret_val;

	switch (phy->type) {
	case igc_phy_i225:
	default:
		/* speed downshift not supported */
		phy->speed_downgraded = false;
		ret_val = 0;
	}

	return ret_val;
}