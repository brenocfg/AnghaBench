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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 e1000e_phy_sw_reset(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_ctrl;

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_ctrl);
	if (ret_val)
		return ret_val;

	phy_ctrl |= BMCR_RESET;
	ret_val = e1e_wphy(hw, MII_BMCR, phy_ctrl);
	if (ret_val)
		return ret_val;

	udelay(1);

	return ret_val;
}