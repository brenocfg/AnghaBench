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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ (* read_reg ) (struct igc_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ MII_SR_AUTONEG_COMPLETE ; 
 scalar_t__ PHY_AUTO_NEG_LIMIT ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct igc_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 (struct igc_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static s32 igc_wait_autoneg(struct igc_hw *hw)
{
	u16 i, phy_status;
	s32 ret_val = 0;

	/* Break after autoneg completes or PHY_AUTO_NEG_LIMIT expires. */
	for (i = PHY_AUTO_NEG_LIMIT; i > 0; i--) {
		ret_val = hw->phy.ops.read_reg(hw, PHY_STATUS, &phy_status);
		if (ret_val)
			break;
		ret_val = hw->phy.ops.read_reg(hw, PHY_STATUS, &phy_status);
		if (ret_val)
			break;
		if (phy_status & MII_SR_AUTONEG_COMPLETE)
			break;
		msleep(100);
	}

	/* PHY_AUTO_NEG_TIME expiration doesn't guarantee auto-negotiation
	 * has completed.
	 */
	return ret_val;
}