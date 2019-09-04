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
struct atl1_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1_write_phy_reg (int /*<<< orphan*/ *,int,int) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mdio_write(struct net_device *netdev, int phy_id, int reg_num,
	int val)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);

	atl1_write_phy_reg(&adapter->hw, reg_num, val);
}