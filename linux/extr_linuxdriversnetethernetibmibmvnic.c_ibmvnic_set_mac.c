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
struct sockaddr {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;
struct ibmvnic_adapter {scalar_t__ state; int mac_change_pending; TYPE_1__ desired; } ;

/* Variables and functions */
 scalar_t__ VNIC_PROBED ; 
 int __ibmvnic_set_mac (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ibmvnic_set_mac(struct net_device *netdev, void *p)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	struct sockaddr *addr = p;
	int rc;

	if (adapter->state == VNIC_PROBED) {
		memcpy(&adapter->desired.mac, addr, sizeof(struct sockaddr));
		adapter->mac_change_pending = true;
		return 0;
	}

	rc = __ibmvnic_set_mac(netdev, addr);

	return rc;
}