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
struct ena_adapter {int /*<<< orphan*/  num_queues; } ;

/* Variables and functions */
 int ena_up (struct ena_adapter*) ; 
 int /*<<< orphan*/  ifup ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ena_open(struct net_device *netdev)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	int rc;

	/* Notify the stack of the actual queue counts. */
	rc = netif_set_real_num_tx_queues(netdev, adapter->num_queues);
	if (rc) {
		netif_err(adapter, ifup, netdev, "Can't set num tx queues\n");
		return rc;
	}

	rc = netif_set_real_num_rx_queues(netdev, adapter->num_queues);
	if (rc) {
		netif_err(adapter, ifup, netdev, "Can't set num rx queues\n");
		return rc;
	}

	rc = ena_up(adapter);
	if (rc)
		return rc;

	return rc;
}