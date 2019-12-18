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
struct qlcnic_adapter {int /*<<< orphan*/  max_jumbo_rxd; int /*<<< orphan*/  max_rxd; int /*<<< orphan*/  num_txd; int /*<<< orphan*/  num_jumbo_rxd; int /*<<< orphan*/  num_rxd; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_jumbo_max_pending; int /*<<< orphan*/  rx_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CMD_DESCRIPTORS ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
qlcnic_get_ringparam(struct net_device *dev,
		struct ethtool_ringparam *ring)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);

	ring->rx_pending = adapter->num_rxd;
	ring->rx_jumbo_pending = adapter->num_jumbo_rxd;
	ring->tx_pending = adapter->num_txd;

	ring->rx_max_pending = adapter->max_rxd;
	ring->rx_jumbo_max_pending = adapter->max_jumbo_rxd;
	ring->tx_max_pending = MAX_CMD_DESCRIPTORS;
}