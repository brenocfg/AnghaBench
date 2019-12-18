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
struct vmxnet3_adapter {int /*<<< orphan*/  rx_ring2_size; int /*<<< orphan*/  rxdata_desc_size; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_mini_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_jumbo_max_pending; int /*<<< orphan*/  rx_mini_max_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_RXDATA_DESC_MAX_SIZE ; 
 int /*<<< orphan*/  VMXNET3_RX_RING2_MAX_SIZE ; 
 int /*<<< orphan*/  VMXNET3_RX_RING_MAX_SIZE ; 
 int /*<<< orphan*/  VMXNET3_TX_RING_MAX_SIZE ; 
 scalar_t__ VMXNET3_VERSION_GE_3 (struct vmxnet3_adapter*) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
vmxnet3_get_ringparam(struct net_device *netdev,
		      struct ethtool_ringparam *param)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	param->rx_max_pending = VMXNET3_RX_RING_MAX_SIZE;
	param->tx_max_pending = VMXNET3_TX_RING_MAX_SIZE;
	param->rx_mini_max_pending = VMXNET3_VERSION_GE_3(adapter) ?
		VMXNET3_RXDATA_DESC_MAX_SIZE : 0;
	param->rx_jumbo_max_pending = VMXNET3_RX_RING2_MAX_SIZE;

	param->rx_pending = adapter->rx_ring_size;
	param->tx_pending = adapter->tx_ring_size;
	param->rx_mini_pending = VMXNET3_VERSION_GE_3(adapter) ?
		adapter->rxdata_desc_size : 0;
	param->rx_jumbo_pending = adapter->rx_ring2_size;
}