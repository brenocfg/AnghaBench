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
struct ibmvnic_adapter {int /*<<< orphan*/  req_rx_queues; int /*<<< orphan*/  req_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_real_num_queues(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	int rc;

	netdev_dbg(netdev, "Setting real tx/rx queues (%llx/%llx)\n",
		   adapter->req_tx_queues, adapter->req_rx_queues);

	rc = netif_set_real_num_tx_queues(netdev, adapter->req_tx_queues);
	if (rc) {
		netdev_err(netdev, "failed to set the number of tx queues\n");
		return rc;
	}

	rc = netif_set_real_num_rx_queues(netdev, adapter->req_rx_queues);
	if (rc)
		netdev_err(netdev, "failed to set the number of rx queues\n");

	return rc;
}