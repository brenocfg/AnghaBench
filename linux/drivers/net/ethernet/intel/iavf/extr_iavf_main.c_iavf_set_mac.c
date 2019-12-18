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
struct iavf_mac_filter {int remove; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct iavf_hw {TYPE_1__ mac; } ;
struct iavf_adapter {int /*<<< orphan*/  mac_vlan_list_lock; int /*<<< orphan*/  aq_required; struct iavf_hw hw; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_DEL_MAC_FILTER ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iavf_mac_filter* iavf_add_filter (struct iavf_adapter*,int /*<<< orphan*/ ) ; 
 struct iavf_mac_filter* iavf_find_filter (struct iavf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iavf_set_mac(struct net_device *netdev, void *p)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);
	struct iavf_hw *hw = &adapter->hw;
	struct iavf_mac_filter *f;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(netdev->dev_addr, addr->sa_data))
		return 0;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	f = iavf_find_filter(adapter, hw->mac.addr);
	if (f) {
		f->remove = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_MAC_FILTER;
	}

	f = iavf_add_filter(adapter, addr->sa_data);

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	if (f) {
		ether_addr_copy(hw->mac.addr, addr->sa_data);
	}

	return (f == NULL) ? -ENOMEM : 0;
}