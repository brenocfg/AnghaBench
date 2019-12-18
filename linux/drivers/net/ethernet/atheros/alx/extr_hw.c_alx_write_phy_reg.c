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
struct alx_hw {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int __alx_write_phy_reg (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int alx_write_phy_reg(struct alx_hw *hw, u16 reg, u16 phy_data)
{
	int err;

	spin_lock(&hw->mdio_lock);
	err = __alx_write_phy_reg(hw, reg, phy_data);
	spin_unlock(&hw->mdio_lock);

	return err;
}