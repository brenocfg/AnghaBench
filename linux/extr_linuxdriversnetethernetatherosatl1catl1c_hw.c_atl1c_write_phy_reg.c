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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int atl1c_write_phy_core (struct atl1c_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int atl1c_write_phy_reg(struct atl1c_hw *hw, u32 reg_addr, u16 phy_data)
{
	return atl1c_write_phy_core(hw, false, 0, reg_addr, phy_data);
}