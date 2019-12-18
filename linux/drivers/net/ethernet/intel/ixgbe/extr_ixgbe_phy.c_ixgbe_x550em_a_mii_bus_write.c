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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct ixgbe_adapter* priv; } ;
struct TYPE_2__ {int phy_semaphore_mask; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_GSSR_PHY0_SM ; 
 int IXGBE_GSSR_TOKEN_SM ; 
 int /*<<< orphan*/  ixgbe_mii_bus_write_generic (struct ixgbe_hw*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_x550em_a_mii_bus_write(struct mii_bus *bus, int addr,
					int regnum, u16 val)
{
	struct ixgbe_adapter *adapter = bus->priv;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 gssr = hw->phy.phy_semaphore_mask;

	gssr |= IXGBE_GSSR_TOKEN_SM | IXGBE_GSSR_PHY0_SM;
	return ixgbe_mii_bus_write_generic(hw, addr, regnum, val, gssr);
}