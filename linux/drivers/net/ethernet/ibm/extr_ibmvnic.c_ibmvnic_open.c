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
struct net_device {int dummy; } ;
struct ibmvnic_adapter {scalar_t__ state; scalar_t__ failover_pending; } ;

/* Variables and functions */
 scalar_t__ VNIC_CLOSED ; 
 scalar_t__ VNIC_OPEN ; 
 int __ibmvnic_open (struct net_device*) ; 
 int ibmvnic_login (struct net_device*) ; 
 int init_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_resources (struct ibmvnic_adapter*) ; 

__attribute__((used)) static int ibmvnic_open(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	int rc;

	/* If device failover is pending, just set device state and return.
	 * Device operation will be handled by reset routine.
	 */
	if (adapter->failover_pending) {
		adapter->state = VNIC_OPEN;
		return 0;
	}

	if (adapter->state != VNIC_CLOSED) {
		rc = ibmvnic_login(netdev);
		if (rc)
			return rc;

		rc = init_resources(adapter);
		if (rc) {
			netdev_err(netdev, "failed to initialize resources\n");
			release_resources(adapter);
			return rc;
		}
	}

	rc = __ibmvnic_open(netdev);

	return rc;
}