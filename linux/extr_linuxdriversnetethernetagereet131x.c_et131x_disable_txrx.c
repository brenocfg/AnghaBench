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
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  et131x_disable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_rx_dma_disable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_disable (struct et131x_adapter*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static void et131x_disable_txrx(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);

	netif_stop_queue(netdev);

	et131x_rx_dma_disable(adapter);
	et131x_tx_dma_disable(adapter);

	et131x_disable_interrupts(adapter);
}