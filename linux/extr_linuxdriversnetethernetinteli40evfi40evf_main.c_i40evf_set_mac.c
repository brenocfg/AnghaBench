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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct i40evf_mac_filter {int remove; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct i40e_hw {TYPE_1__ mac; } ;
struct i40evf_adapter {int flags; struct i40e_hw hw; int /*<<< orphan*/  mac_vlan_list_lock; int /*<<< orphan*/  aq_required; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int EPERM ; 
 int I40EVF_FLAG_ADDR_SET_BY_PF ; 
 int /*<<< orphan*/  I40EVF_FLAG_AQ_DEL_MAC_FILTER ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40evf_mac_filter* i40evf_add_filter (struct i40evf_adapter*,int /*<<< orphan*/ ) ; 
 struct i40evf_mac_filter* i40evf_find_filter (struct i40evf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40evf_set_mac(struct net_device *netdev, void *p)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	struct i40e_hw *hw = &adapter->hw;
	struct i40evf_mac_filter *f;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(netdev->dev_addr, addr->sa_data))
		return 0;

	if (adapter->flags & I40EVF_FLAG_ADDR_SET_BY_PF)
		return -EPERM;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = i40evf_find_filter(adapter, hw->mac.addr);
	if (f) {
		f->remove = true;
		adapter->aq_required |= I40EVF_FLAG_AQ_DEL_MAC_FILTER;
	}

	f = i40evf_add_filter(adapter, addr->sa_data);

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	if (f) {
		ether_addr_copy(hw->mac.addr, addr->sa_data);
		ether_addr_copy(netdev->dev_addr, adapter->hw.mac.addr);
	}

	return (f == NULL) ? -ENOMEM : 0;
}