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
struct TYPE_2__ {int /*<<< orphan*/  power_down; int /*<<< orphan*/  power_up; } ;
struct e1000_phy_info {scalar_t__ media_type; int addr; int reset_delay_us; scalar_t__ id; int /*<<< orphan*/  type; int /*<<< orphan*/  autoneg_mask; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 scalar_t__ GG82563_E_PHY_ID ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_phy_gg82563 ; 
 int /*<<< orphan*/  e1000_phy_none ; 
 int /*<<< orphan*/  e1000_power_down_phy_copper_80003es2lan ; 
 int /*<<< orphan*/  e1000_power_up_phy_copper ; 
 int /*<<< orphan*/  e1000e_get_phy_id (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_phy_params_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	if (hw->phy.media_type != e1000_media_type_copper) {
		phy->type = e1000_phy_none;
		return 0;
	} else {
		phy->ops.power_up = e1000_power_up_phy_copper;
		phy->ops.power_down = e1000_power_down_phy_copper_80003es2lan;
	}

	phy->addr = 1;
	phy->autoneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us = 100;
	phy->type = e1000_phy_gg82563;

	/* This can only be done after all function pointers are setup. */
	ret_val = e1000e_get_phy_id(hw);

	/* Verify phy id */
	if (phy->id != GG82563_E_PHY_ID)
		return -E1000_ERR_PHY;

	return ret_val;
}