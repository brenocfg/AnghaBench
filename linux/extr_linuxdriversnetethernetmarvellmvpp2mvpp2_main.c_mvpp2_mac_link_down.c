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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mvpp2_port {int /*<<< orphan*/  has_phy; scalar_t__ base; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 scalar_t__ MVPP2_GMAC_AUTONEG_CONFIG ; 
 int /*<<< orphan*/  MVPP2_GMAC_FORCE_LINK_DOWN ; 
 int /*<<< orphan*/  MVPP2_GMAC_FORCE_LINK_PASS ; 
 scalar_t__ PHY_INTERFACE_MODE_10GKR ; 
 int /*<<< orphan*/  mvpp2_egress_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_ingress_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_port_disable (struct mvpp2_port*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phylink_autoneg_inband (unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvpp2_mac_link_down(struct net_device *dev, unsigned int mode,
				phy_interface_t interface)
{
	struct mvpp2_port *port = netdev_priv(dev);
	u32 val;

	if (!phylink_autoneg_inband(mode) &&
	    interface != PHY_INTERFACE_MODE_10GKR) {
		val = readl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
		val &= ~MVPP2_GMAC_FORCE_LINK_PASS;
		val |= MVPP2_GMAC_FORCE_LINK_DOWN;
		writel(val, port->base + MVPP2_GMAC_AUTONEG_CONFIG);
	}

	netif_tx_stop_all_queues(dev);
	mvpp2_egress_disable(port);
	mvpp2_ingress_disable(port);

	/* When using link interrupts to notify phylink of a MAC state change,
	 * we do not want the port to be disabled (we want to receive further
	 * interrupts, to be notified when the port will have a link later).
	 */
	if (!port->has_phy)
		return;

	mvpp2_port_disable(port);
}