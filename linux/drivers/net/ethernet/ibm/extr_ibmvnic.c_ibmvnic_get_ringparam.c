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
struct ibmvnic_adapter {int priv_flags; int /*<<< orphan*/  req_tx_entries_per_subcrq; int /*<<< orphan*/  req_rx_add_entries_per_subcrq; void* max_tx_entries_per_subcrq; void* max_rx_add_entries_per_subcrq; } ;
struct ethtool_ringparam {scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; void* tx_max_pending; void* rx_max_pending; } ;

/* Variables and functions */
 void* IBMVNIC_MAX_QUEUE_SZ ; 
 int IBMVNIC_USE_SERVER_MAXES ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ibmvnic_get_ringparam(struct net_device *netdev,
				  struct ethtool_ringparam *ring)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	if (adapter->priv_flags & IBMVNIC_USE_SERVER_MAXES) {
		ring->rx_max_pending = adapter->max_rx_add_entries_per_subcrq;
		ring->tx_max_pending = adapter->max_tx_entries_per_subcrq;
	} else {
		ring->rx_max_pending = IBMVNIC_MAX_QUEUE_SZ;
		ring->tx_max_pending = IBMVNIC_MAX_QUEUE_SZ;
	}
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_pending = adapter->req_rx_add_entries_per_subcrq;
	ring->tx_pending = adapter->req_tx_entries_per_subcrq;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
}