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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct qlcnic_adapter {int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mac_addr; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int QLCNIC_MAC_OVERRIDE_DISABLED ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 scalar_t__ ether_addr_equal_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_delete_adapter_mac (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_napi_disable (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_napi_enable (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_set_multi (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_set_mac(struct net_device *netdev, void *p)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct sockaddr *addr = p;

	if (qlcnic_sriov_vf_check(adapter))
		return -EINVAL;

	if ((adapter->flags & QLCNIC_MAC_OVERRIDE_DISABLED))
		return -EOPNOTSUPP;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EINVAL;

	if (ether_addr_equal_unaligned(adapter->mac_addr, addr->sa_data) &&
	    ether_addr_equal_unaligned(netdev->dev_addr, addr->sa_data))
		return 0;

	if (test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		netif_device_detach(netdev);
		qlcnic_napi_disable(adapter);
	}

	qlcnic_delete_adapter_mac(adapter);
	memcpy(adapter->mac_addr, addr->sa_data, netdev->addr_len);
	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	qlcnic_set_multi(adapter->netdev);

	if (test_bit(__QLCNIC_DEV_UP, &adapter->state)) {
		netif_device_attach(netdev);
		qlcnic_napi_enable(adapter);
	}
	return 0;
}