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
typedef  int /*<<< orphan*/  u64 ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ibmveth_adapter {int /*<<< orphan*/  netdev; TYPE_1__* vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int h_change_logical_lan_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmveth_encode_mac_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ibmveth_set_mac_addr(struct net_device *dev, void *p)
{
	struct ibmveth_adapter *adapter = netdev_priv(dev);
	struct sockaddr *addr = p;
	u64 mac_address;
	int rc;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	mac_address = ibmveth_encode_mac_addr(addr->sa_data);
	rc = h_change_logical_lan_mac(adapter->vdev->unit_address, mac_address);
	if (rc) {
		netdev_err(adapter->netdev, "h_change_logical_lan_mac failed with rc=%d\n", rc);
		return rc;
	}

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	return 0;
}