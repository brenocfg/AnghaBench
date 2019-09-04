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
struct TYPE_2__ {scalar_t__ port_type; } ;
struct netxen_adapter {TYPE_1__ ahw; int /*<<< orphan*/  num_txd; scalar_t__ num_lro_rxd; int /*<<< orphan*/  num_jumbo_rxd; int /*<<< orphan*/  num_rxd; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_jumbo_max_pending; int /*<<< orphan*/  rx_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CMD_DESCRIPTORS ; 
 int /*<<< orphan*/  MAX_JUMBO_RCV_DESCRIPTORS_10G ; 
 int /*<<< orphan*/  MAX_JUMBO_RCV_DESCRIPTORS_1G ; 
 int /*<<< orphan*/  MAX_RCV_DESCRIPTORS_10G ; 
 int /*<<< orphan*/  MAX_RCV_DESCRIPTORS_1G ; 
 scalar_t__ NETXEN_NIC_GBE ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
netxen_nic_get_ringparam(struct net_device *dev,
		struct ethtool_ringparam *ring)
{
	struct netxen_adapter *adapter = netdev_priv(dev);

	ring->rx_pending = adapter->num_rxd;
	ring->rx_jumbo_pending = adapter->num_jumbo_rxd;
	ring->rx_jumbo_pending += adapter->num_lro_rxd;
	ring->tx_pending = adapter->num_txd;

	if (adapter->ahw.port_type == NETXEN_NIC_GBE) {
		ring->rx_max_pending = MAX_RCV_DESCRIPTORS_1G;
		ring->rx_jumbo_max_pending = MAX_JUMBO_RCV_DESCRIPTORS_1G;
	} else {
		ring->rx_max_pending = MAX_RCV_DESCRIPTORS_10G;
		ring->rx_jumbo_max_pending = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	}

	ring->tx_max_pending = MAX_CMD_DESCRIPTORS;
}