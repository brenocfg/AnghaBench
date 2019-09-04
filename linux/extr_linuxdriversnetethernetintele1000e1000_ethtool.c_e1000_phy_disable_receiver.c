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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int,int) ; 

__attribute__((used)) static void e1000_phy_disable_receiver(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	/* Write out to PHY registers 29 and 30 to disable the Receiver. */
	e1000_write_phy_reg(hw, 29, 0x001F);
	e1000_write_phy_reg(hw, 30, 0x8FFC);
	e1000_write_phy_reg(hw, 29, 0x001A);
	e1000_write_phy_reg(hw, 30, 0x8FF0);
}