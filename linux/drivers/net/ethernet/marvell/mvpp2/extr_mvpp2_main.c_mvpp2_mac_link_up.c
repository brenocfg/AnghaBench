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
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct mvpp2_port {scalar_t__ base; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP22_XLG_CTRL0_FORCE_LINK_DOWN ; 
 int /*<<< orphan*/  MVPP22_XLG_CTRL0_FORCE_LINK_PASS ; 
 scalar_t__ MVPP22_XLG_CTRL0_REG ; 
 scalar_t__ MVPP2_GMAC_AUTONEG_CONFIG ; 
 int /*<<< orphan*/  MVPP2_GMAC_FORCE_LINK_DOWN ; 
 int /*<<< orphan*/  MVPP2_GMAC_FORCE_LINK_PASS ; 
 int /*<<< orphan*/  mvpp2_egress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_ingress_enable (struct mvpp2_port*) ; 
 scalar_t__ mvpp2_is_xlg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_port_enable (struct mvpp2_port*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phylink_autoneg_inband (unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvpp2_mac_link_up(struct phylink_config *config, unsigned int mode,
			      phy_interface_t interface, struct phy_device *phy)
{
	struct net_device *dev = to_net_dev(config->dev);
	struct mvpp2_port *port = netdev_priv(dev);
	u32 val;

	if (!phylink_autoneg_inband(mode)) {
		if (mvpp2_is_xlg(interface)) {
			val = readl(port->base + MVPP22_XLG_CTRL0_REG);
			val &= ~MVPP22_XLG_CTRL0_FORCE_LINK_DOWN;
			val |= MVPP22_XLG_CTRL0_FORCE_LINK_PASS;
			writel(val, port->base + MVPP22_XLG_CTRL0_REG);
		} else {
			val = readl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
			val &= ~MVPP2_GMAC_FORCE_LINK_DOWN;
			val |= MVPP2_GMAC_FORCE_LINK_PASS;
			writel(val, port->base + MVPP2_GMAC_AUTONEG_CONFIG);
		}
	}

	mvpp2_port_enable(port);

	mvpp2_egress_enable(port);
	mvpp2_ingress_enable(port);
	netif_tx_wake_all_queues(dev);
}