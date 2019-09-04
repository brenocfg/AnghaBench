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
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; int flags; int /*<<< orphan*/  active_vlans; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IGB_FLAG_VLAN_PROMISC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_vfta_set (struct e1000_hw*,int /*<<< orphan*/ ,int,int,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_vlan_rx_kill_vid(struct net_device *netdev,
				__be16 proto, u16 vid)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	int pf_id = adapter->vfs_allocated_count;
	struct e1000_hw *hw = &adapter->hw;

	/* remove VID from filter table */
	if (vid && !(adapter->flags & IGB_FLAG_VLAN_PROMISC))
		igb_vfta_set(hw, vid, pf_id, false, true);

	clear_bit(vid, adapter->active_vlans);

	return 0;
}