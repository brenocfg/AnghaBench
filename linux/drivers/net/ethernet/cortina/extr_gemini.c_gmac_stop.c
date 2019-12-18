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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  phydev; } ;
struct gemini_ethernet_port {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_coalesce_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  gmac_cleanup_rxq (struct net_device*) ; 
 int /*<<< orphan*/  gmac_cleanup_txqs (struct net_device*) ; 
 int /*<<< orphan*/  gmac_disable_tx_rx (struct net_device*) ; 
 int /*<<< orphan*/  gmac_enable_irq (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmac_stop_dma (struct gemini_ethernet_port*) ; 
 int /*<<< orphan*/  gmac_update_hw_stats (struct net_device*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmac_stop(struct net_device *netdev)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);

	hrtimer_cancel(&port->rx_coalesce_timer);
	netif_tx_stop_all_queues(netdev);
	gmac_disable_tx_rx(netdev);
	gmac_stop_dma(port);
	napi_disable(&port->napi);

	gmac_enable_irq(netdev, 0);
	gmac_cleanup_rxq(netdev);
	gmac_cleanup_txqs(netdev);

	phy_stop(netdev->phydev);
	free_irq(netdev->irq, netdev);

	gmac_update_hw_stats(netdev);
	return 0;
}