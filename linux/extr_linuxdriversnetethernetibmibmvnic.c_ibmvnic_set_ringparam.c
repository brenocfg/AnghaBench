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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ rx_entries; scalar_t__ tx_entries; } ;
struct ibmvnic_adapter {scalar_t__ max_rx_add_entries_per_subcrq; scalar_t__ max_tx_entries_per_subcrq; TYPE_1__ desired; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int wait_for_reset (struct ibmvnic_adapter*) ; 

__attribute__((used)) static int ibmvnic_set_ringparam(struct net_device *netdev,
				 struct ethtool_ringparam *ring)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	if (ring->rx_pending > adapter->max_rx_add_entries_per_subcrq  ||
	    ring->tx_pending > adapter->max_tx_entries_per_subcrq) {
		netdev_err(netdev, "Invalid request.\n");
		netdev_err(netdev, "Max tx buffers = %llu\n",
			   adapter->max_rx_add_entries_per_subcrq);
		netdev_err(netdev, "Max rx buffers = %llu\n",
			   adapter->max_tx_entries_per_subcrq);
		return -EINVAL;
	}

	adapter->desired.rx_entries = ring->rx_pending;
	adapter->desired.tx_entries = ring->tx_pending;

	return wait_for_reset(adapter);
}