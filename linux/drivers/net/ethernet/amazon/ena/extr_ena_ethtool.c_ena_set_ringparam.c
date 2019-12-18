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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ tx_pending; scalar_t__ rx_pending; } ;
struct ena_adapter {scalar_t__ requested_tx_ring_size; scalar_t__ requested_rx_ring_size; } ;

/* Variables and functions */
 scalar_t__ ENA_MIN_RING_SIZE ; 
 int ena_update_queue_sizes (struct ena_adapter*,scalar_t__,scalar_t__) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ rounddown_pow_of_two (scalar_t__) ; 

__attribute__((used)) static int ena_set_ringparam(struct net_device *netdev,
			     struct ethtool_ringparam *ring)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	u32 new_tx_size, new_rx_size;

	new_tx_size = ring->tx_pending < ENA_MIN_RING_SIZE ?
			ENA_MIN_RING_SIZE : ring->tx_pending;
	new_tx_size = rounddown_pow_of_two(new_tx_size);

	new_rx_size = ring->rx_pending < ENA_MIN_RING_SIZE ?
			ENA_MIN_RING_SIZE : ring->rx_pending;
	new_rx_size = rounddown_pow_of_two(new_rx_size);

	if (new_tx_size == adapter->requested_tx_ring_size &&
	    new_rx_size == adapter->requested_rx_ring_size)
		return 0;

	return ena_update_queue_sizes(adapter, new_tx_size, new_rx_size);
}