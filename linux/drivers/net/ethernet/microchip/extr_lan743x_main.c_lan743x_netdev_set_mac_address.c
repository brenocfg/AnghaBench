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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int eth_prepare_mac_addr_change (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_mac_set_address (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_rfe_update_mac_address (struct lan743x_adapter*) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_netdev_set_mac_address(struct net_device *netdev,
					  void *addr)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	struct sockaddr *sock_addr = addr;
	int ret;

	ret = eth_prepare_mac_addr_change(netdev, sock_addr);
	if (ret)
		return ret;
	ether_addr_copy(netdev->dev_addr, sock_addr->sa_data);
	lan743x_mac_set_address(adapter, sock_addr->sa_data);
	lan743x_rfe_update_mac_address(adapter);
	return 0;
}