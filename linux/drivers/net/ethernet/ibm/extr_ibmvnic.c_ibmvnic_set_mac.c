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
struct net_device {int dummy; } ;
struct ibmvnic_adapter {scalar_t__ state; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 scalar_t__ VNIC_PROBED ; 
 int __ibmvnic_set_mac (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ibmvnic_set_mac(struct net_device *netdev, void *p)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	struct sockaddr *addr = p;
	int rc;

	rc = 0;
	ether_addr_copy(adapter->mac_addr, addr->sa_data);
	if (adapter->state != VNIC_PROBED)
		rc = __ibmvnic_set_mac(netdev, addr->sa_data);

	return rc;
}