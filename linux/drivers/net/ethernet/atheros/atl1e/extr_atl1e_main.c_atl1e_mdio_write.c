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
struct net_device {int dummy; } ;
struct atl1e_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int MDIO_REG_ADDR_MASK ; 
 scalar_t__ atl1e_write_phy_reg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl1e_mdio_write(struct net_device *netdev, int phy_id,
			     int reg_num, int val)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);

	if (atl1e_write_phy_reg(&adapter->hw,
				reg_num & MDIO_REG_ADDR_MASK, val))
		netdev_err(netdev, "write phy register failed\n");
}