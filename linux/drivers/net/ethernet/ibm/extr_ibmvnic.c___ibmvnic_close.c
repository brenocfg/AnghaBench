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
struct ibmvnic_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_LOGICAL_LNK_DN ; 
 int /*<<< orphan*/  VNIC_CLOSED ; 
 int /*<<< orphan*/  VNIC_CLOSING ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int set_link_state (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ibmvnic_close(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	int rc = 0;

	adapter->state = VNIC_CLOSING;
	rc = set_link_state(adapter, IBMVNIC_LOGICAL_LNK_DN);
	if (rc)
		return rc;
	adapter->state = VNIC_CLOSED;
	return 0;
}