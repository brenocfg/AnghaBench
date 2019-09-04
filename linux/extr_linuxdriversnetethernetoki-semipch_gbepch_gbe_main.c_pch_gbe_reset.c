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
struct pch_gbe_hw {int dummy; } ;
struct pch_gbe_adapter {struct net_device* netdev; struct pch_gbe_hw hw; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_GBE_MAR_ENTRIES ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  pch_gbe_mac_init_rx_addrs (struct pch_gbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_mac_reset_hw (struct pch_gbe_hw*) ; 
 scalar_t__ pch_gbe_phy_get_id (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_init_setting (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_set_rgmii (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_set_multi (struct net_device*) ; 

void pch_gbe_reset(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pch_gbe_hw *hw = &adapter->hw;
	s32 ret_val;

	pch_gbe_mac_reset_hw(hw);
	/* reprogram multicast address register after reset */
	pch_gbe_set_multi(netdev);
	/* Setup the receive address. */
	pch_gbe_mac_init_rx_addrs(hw, PCH_GBE_MAR_ENTRIES);

	ret_val = pch_gbe_phy_get_id(hw);
	if (ret_val) {
		netdev_err(adapter->netdev, "pch_gbe_phy_get_id error\n");
		return;
	}
	pch_gbe_phy_init_setting(hw);
	/* Setup Mac interface option RGMII */
	pch_gbe_phy_set_rgmii(hw);
}