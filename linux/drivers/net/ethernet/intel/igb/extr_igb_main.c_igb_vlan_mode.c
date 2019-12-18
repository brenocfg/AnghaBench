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
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  vfs_allocated_count; struct e1000_hw hw; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_VME ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int /*<<< orphan*/  E1000_RCTL_CFIEN ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  igb_set_vf_vlan_strip (struct igb_adapter*,int /*<<< orphan*/ ,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_vlan_mode(struct net_device *netdev, netdev_features_t features)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl, rctl;
	bool enable = !!(features & NETIF_F_HW_VLAN_CTAG_RX);

	if (enable) {
		/* enable VLAN tag insert/strip */
		ctrl = rd32(E1000_CTRL);
		ctrl |= E1000_CTRL_VME;
		wr32(E1000_CTRL, ctrl);

		/* Disable CFI check */
		rctl = rd32(E1000_RCTL);
		rctl &= ~E1000_RCTL_CFIEN;
		wr32(E1000_RCTL, rctl);
	} else {
		/* disable VLAN tag insert/strip */
		ctrl = rd32(E1000_CTRL);
		ctrl &= ~E1000_CTRL_VME;
		wr32(E1000_CTRL, ctrl);
	}

	igb_set_vf_vlan_strip(adapter, adapter->vfs_allocated_count, enable);
}