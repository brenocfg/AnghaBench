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
union gmac_config0 {int /*<<< orphan*/  bits32; } ;
struct net_device {int dummy; } ;
struct gemini_ethernet_port {int rxq_order; int txq_order; scalar_t__ gmac_base; } ;
struct ethtool_ringparam {int rx_max_pending; int tx_max_pending; int rx_pending; int tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; } ;

/* Variables and functions */
 scalar_t__ GMAC_CONFIG0 ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void gmac_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *rp)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	union gmac_config0 config0;

	config0.bits32 = readl(port->gmac_base + GMAC_CONFIG0);

	rp->rx_max_pending = 1 << 15;
	rp->rx_mini_max_pending = 0;
	rp->rx_jumbo_max_pending = 0;
	rp->tx_max_pending = 1 << 15;

	rp->rx_pending = 1 << port->rxq_order;
	rp->rx_mini_pending = 0;
	rp->rx_jumbo_pending = 0;
	rp->tx_pending = 1 << port->txq_order;
}