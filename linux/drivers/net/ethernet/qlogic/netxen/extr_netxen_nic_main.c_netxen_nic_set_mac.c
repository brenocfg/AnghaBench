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
struct netxen_adapter {int /*<<< orphan*/  (* macaddr_set ) (struct netxen_adapter*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mac_addr; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netxen_napi_disable (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_napi_enable (struct netxen_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netxen_nic_set_mac(struct net_device *netdev, void *p)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (netif_running(netdev)) {
		netif_device_detach(netdev);
		netxen_napi_disable(adapter);
	}

	memcpy(adapter->mac_addr, addr->sa_data, netdev->addr_len);
	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	adapter->macaddr_set(adapter, addr->sa_data);

	if (netif_running(netdev)) {
		netif_device_attach(netdev);
		netxen_napi_enable(adapter);
	}
	return 0;
}