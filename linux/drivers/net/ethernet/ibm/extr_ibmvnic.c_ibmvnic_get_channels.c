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
struct ibmvnic_adapter {int priv_flags; int /*<<< orphan*/  req_tx_queues; int /*<<< orphan*/  req_rx_queues; void* max_tx_queues; void* max_rx_queues; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; scalar_t__ max_combined; scalar_t__ max_other; void* max_tx; void* max_rx; } ;

/* Variables and functions */
 void* IBMVNIC_MAX_QUEUES ; 
 int IBMVNIC_USE_SERVER_MAXES ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ibmvnic_get_channels(struct net_device *netdev,
				 struct ethtool_channels *channels)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	if (adapter->priv_flags & IBMVNIC_USE_SERVER_MAXES) {
		channels->max_rx = adapter->max_rx_queues;
		channels->max_tx = adapter->max_tx_queues;
	} else {
		channels->max_rx = IBMVNIC_MAX_QUEUES;
		channels->max_tx = IBMVNIC_MAX_QUEUES;
	}

	channels->max_other = 0;
	channels->max_combined = 0;
	channels->rx_count = adapter->req_rx_queues;
	channels->tx_count = adapter->req_tx_queues;
	channels->other_count = 0;
	channels->combined_count = 0;
}