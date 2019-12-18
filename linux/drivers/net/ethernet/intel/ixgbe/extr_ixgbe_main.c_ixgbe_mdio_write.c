#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int (* write_reg ) (struct ixgbe_hw*,int,int,int) ;} ;
struct TYPE_4__ {int prtad; } ;
struct TYPE_6__ {TYPE_2__ ops; TYPE_1__ mdio; } ;
struct ixgbe_hw {TYPE_3__ phy; } ;
struct ixgbe_adapter {scalar_t__ mii_bus; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int MDIO_DEVAD_NONE ; 
 int MII_ADDR_C45 ; 
 int mdiobus_write (scalar_t__,int,int,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int stub1 (struct ixgbe_hw*,int,int,int) ; 

__attribute__((used)) static int ixgbe_mdio_write(struct net_device *netdev, int prtad, int devad,
			    u16 addr, u16 value)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;

	if (adapter->mii_bus) {
		int regnum = addr;

		if (devad != MDIO_DEVAD_NONE)
			regnum |= (devad << 16) | MII_ADDR_C45;

		return mdiobus_write(adapter->mii_bus, prtad, regnum, value);
	}

	if (prtad != hw->phy.mdio.prtad)
		return -EINVAL;
	return hw->phy.ops.write_reg(hw, addr, devad, value);
}