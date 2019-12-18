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
struct pch_gbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CR_RESET ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  pch_gbe_phy_read_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_phy_write_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pch_gbe_phy_sw_reset(struct pch_gbe_hw *hw)
{
	u16 phy_ctrl;

	pch_gbe_phy_read_reg_miic(hw, PHY_CONTROL, &phy_ctrl);
	phy_ctrl |= MII_CR_RESET;
	pch_gbe_phy_write_reg_miic(hw, PHY_CONTROL, phy_ctrl);
	udelay(1);
}