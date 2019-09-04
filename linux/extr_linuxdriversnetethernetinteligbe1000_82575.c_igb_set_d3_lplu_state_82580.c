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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_phy_info {scalar_t__ smart_speed; scalar_t__ autoneg_advertised; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_82580_PHY_POWER_MGMT ; 
 int /*<<< orphan*/  E1000_82580_PM_D3_LPLU ; 
 int /*<<< orphan*/  E1000_82580_PM_SPD ; 
 scalar_t__ E1000_ALL_10_SPEED ; 
 scalar_t__ E1000_ALL_NOT_GIG ; 
 scalar_t__ E1000_ALL_SPEED_DUPLEX ; 
 scalar_t__ e1000_smart_speed_off ; 
 scalar_t__ e1000_smart_speed_on ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_set_d3_lplu_state_82580(struct e1000_hw *hw, bool active)
{
	struct e1000_phy_info *phy = &hw->phy;
	u16 data;

	data = rd32(E1000_82580_PHY_POWER_MGMT);

	if (!active) {
		data &= ~E1000_82580_PM_D3_LPLU;
		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the power conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so performance is maintained.
		 */
		if (phy->smart_speed == e1000_smart_speed_on)
			data |= E1000_82580_PM_SPD;
		else if (phy->smart_speed == e1000_smart_speed_off)
			data &= ~E1000_82580_PM_SPD;
	} else if ((phy->autoneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
		   (phy->autoneg_advertised == E1000_ALL_NOT_GIG) ||
		   (phy->autoneg_advertised == E1000_ALL_10_SPEED)) {
		data |= E1000_82580_PM_D3_LPLU;
		/* When LPLU is enabled, we should disable SmartSpeed */
		data &= ~E1000_82580_PM_SPD;
	}

	wr32(E1000_82580_PHY_POWER_MGMT, data);
	return 0;
}