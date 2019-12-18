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
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_DBG_ADDR ; 
 int /*<<< orphan*/  MII_DBG_DATA ; 
 int atl1c_write_phy_reg (struct atl1c_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int atl1c_write_phy_dbg(struct atl1c_hw *hw, u16 reg_addr, u16 phy_data)
{
	int err;

	err = atl1c_write_phy_reg(hw, MII_DBG_ADDR, reg_addr);
	if (unlikely(err))
		return err;
	else
		err = atl1c_write_phy_reg(hw, MII_DBG_DATA, phy_data);

	return err;
}