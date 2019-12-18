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
struct gemini_ethernet_port {int txq_order; int irq_every_tx_packets; void* rxq_order; } ;
struct ethtool_ringparam {scalar_t__ tx_pending; scalar_t__ rx_pending; } ;

/* Variables and functions */
 int EBUSY ; 
 int geth_resize_freeq (struct gemini_ethernet_port*) ; 
 scalar_t__ ilog2 (scalar_t__) ; 
 void* min (int,scalar_t__) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int gmac_set_ringparam(struct net_device *netdev,
			      struct ethtool_ringparam *rp)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	int err = 0;

	if (netif_running(netdev))
		return -EBUSY;

	if (rp->rx_pending) {
		port->rxq_order = min(15, ilog2(rp->rx_pending - 1) + 1);
		err = geth_resize_freeq(port);
	}
	if (rp->tx_pending) {
		port->txq_order = min(15, ilog2(rp->tx_pending - 1) + 1);
		port->irq_every_tx_packets = 1 << (port->txq_order - 2);
	}

	return err;
}