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
struct ibmvnic_adapter {int /*<<< orphan*/  req_tx_queues; int /*<<< orphan*/  req_rx_queues; int /*<<< orphan*/  max_tx_queues; int /*<<< orphan*/  max_rx_queues; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; scalar_t__ max_combined; scalar_t__ max_other; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ibmvnic_get_channels(struct net_device *netdev,
				 struct ethtool_channels *channels)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	channels->max_rx = adapter->max_rx_queues;
	channels->max_tx = adapter->max_tx_queues;
	channels->max_other = 0;
	channels->max_combined = 0;
	channels->rx_count = adapter->req_rx_queues;
	channels->tx_count = adapter->req_tx_queues;
	channels->other_count = 0;
	channels->combined_count = 0;
}