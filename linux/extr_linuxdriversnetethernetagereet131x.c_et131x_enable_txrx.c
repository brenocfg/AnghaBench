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
struct et131x_adapter {int flags; } ;

/* Variables and functions */
 int FMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  et131x_enable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_rx_dma_enable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_enable (struct et131x_adapter*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static void et131x_enable_txrx(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);

	et131x_rx_dma_enable(adapter);
	et131x_tx_dma_enable(adapter);

	if (adapter->flags & FMP_ADAPTER_INTERRUPT_IN_USE)
		et131x_enable_interrupts(adapter);

	netif_start_queue(netdev);
}