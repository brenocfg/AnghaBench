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
typedef  int u16 ;
struct atl2_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_DBG_ADDR ; 
 int /*<<< orphan*/  MII_DBG_DATA ; 
 int /*<<< orphan*/  atl2_read_phy_reg (struct atl2_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  atl2_write_phy_reg (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atl2_force_ps(struct atl2_hw *hw)
{
	u16 phy_val;

	atl2_write_phy_reg(hw, MII_DBG_ADDR, 0);
	atl2_read_phy_reg(hw, MII_DBG_DATA, &phy_val);
	atl2_write_phy_reg(hw, MII_DBG_DATA, phy_val | 0x1000);

	atl2_write_phy_reg(hw, MII_DBG_ADDR, 2);
	atl2_write_phy_reg(hw, MII_DBG_DATA, 0x3000);
	atl2_write_phy_reg(hw, MII_DBG_ADDR, 3);
	atl2_write_phy_reg(hw, MII_DBG_DATA, 0);
}