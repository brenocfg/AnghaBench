#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pch_gbe_tx_ring {int dummy; } ;
struct pch_gbe_rx_ring {int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ mac; } ;
struct pch_gbe_adapter {struct net_device* netdev; int /*<<< orphan*/  napi; int /*<<< orphan*/  watchdog_timer; TYPE_2__ hw; int /*<<< orphan*/  tx_queue_len; struct pch_gbe_rx_ring* rx_ring; struct pch_gbe_tx_ring* tx_ring; } ;
struct net_device {int /*<<< orphan*/  tx_queue_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_alloc_rx_buffers (struct pch_gbe_adapter*,struct pch_gbe_rx_ring*,int /*<<< orphan*/ ) ; 
 int pch_gbe_alloc_rx_buffers_pool (struct pch_gbe_adapter*,struct pch_gbe_rx_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_alloc_tx_buffers (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*) ; 
 int /*<<< orphan*/  pch_gbe_configure_rx (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_configure_tx (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_enable_dma_rx (TYPE_2__*) ; 
 int /*<<< orphan*/  pch_gbe_enable_mac_rx (TYPE_2__*) ; 
 int /*<<< orphan*/  pch_gbe_free_irq (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_irq_enable (struct pch_gbe_adapter*) ; 
 int pch_gbe_request_irq (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_set_multi (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_setup_rctl (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_setup_tctl (struct pch_gbe_adapter*) ; 

int pch_gbe_up(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pch_gbe_tx_ring *tx_ring = adapter->tx_ring;
	struct pch_gbe_rx_ring *rx_ring = adapter->rx_ring;
	int err = -EINVAL;

	/* Ensure we have a valid MAC */
	if (!is_valid_ether_addr(adapter->hw.mac.addr)) {
		netdev_err(netdev, "Error: Invalid MAC address\n");
		goto out;
	}

	/* hardware has been reset, we need to reload some things */
	pch_gbe_set_multi(netdev);

	pch_gbe_setup_tctl(adapter);
	pch_gbe_configure_tx(adapter);
	pch_gbe_setup_rctl(adapter);
	pch_gbe_configure_rx(adapter);

	err = pch_gbe_request_irq(adapter);
	if (err) {
		netdev_err(netdev,
			   "Error: can't bring device up - irq request failed\n");
		goto out;
	}
	err = pch_gbe_alloc_rx_buffers_pool(adapter, rx_ring, rx_ring->count);
	if (err) {
		netdev_err(netdev,
			   "Error: can't bring device up - alloc rx buffers pool failed\n");
		goto freeirq;
	}
	pch_gbe_alloc_tx_buffers(adapter, tx_ring);
	pch_gbe_alloc_rx_buffers(adapter, rx_ring, rx_ring->count);
	adapter->tx_queue_len = netdev->tx_queue_len;
	pch_gbe_enable_dma_rx(&adapter->hw);
	pch_gbe_enable_mac_rx(&adapter->hw);

	mod_timer(&adapter->watchdog_timer, jiffies);

	napi_enable(&adapter->napi);
	pch_gbe_irq_enable(adapter);
	netif_start_queue(adapter->netdev);

	return 0;

freeirq:
	pch_gbe_free_irq(adapter);
out:
	return err;
}