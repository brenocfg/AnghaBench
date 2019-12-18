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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mvpp2_port {scalar_t__ gop_id; scalar_t__ phy_interface; scalar_t__ phylink; scalar_t__ base; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MVPP22_GMAC_INT_STAT ; 
 int MVPP22_GMAC_INT_STAT_LINK ; 
 scalar_t__ MVPP22_XLG_INT_STAT ; 
 int MVPP22_XLG_INT_STAT_LINK ; 
 scalar_t__ MVPP22_XLG_STATUS ; 
 int MVPP22_XLG_STATUS_LINK_UP ; 
 scalar_t__ MVPP2_GMAC_STATUS0 ; 
 int MVPP2_GMAC_STATUS0_LINK_UP ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  mvpp22_gop_mask_irq (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_gop_unmask_irq (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_egress_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_egress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_ingress_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_ingress_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_interrupts_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_interrupts_enable (struct mvpp2_port*) ; 
 scalar_t__ mvpp2_is_xlg (scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 scalar_t__ phy_interface_mode_is_8023z (scalar_t__) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  phylink_mac_change (scalar_t__,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t mvpp2_link_status_isr(int irq, void *dev_id)
{
	struct mvpp2_port *port = (struct mvpp2_port *)dev_id;
	struct net_device *dev = port->dev;
	bool event = false, link = false;
	u32 val;

	mvpp22_gop_mask_irq(port);

	if (port->gop_id == 0 && mvpp2_is_xlg(port->phy_interface)) {
		val = readl(port->base + MVPP22_XLG_INT_STAT);
		if (val & MVPP22_XLG_INT_STAT_LINK) {
			event = true;
			val = readl(port->base + MVPP22_XLG_STATUS);
			if (val & MVPP22_XLG_STATUS_LINK_UP)
				link = true;
		}
	} else if (phy_interface_mode_is_rgmii(port->phy_interface) ||
		   phy_interface_mode_is_8023z(port->phy_interface) ||
		   port->phy_interface == PHY_INTERFACE_MODE_SGMII) {
		val = readl(port->base + MVPP22_GMAC_INT_STAT);
		if (val & MVPP22_GMAC_INT_STAT_LINK) {
			event = true;
			val = readl(port->base + MVPP2_GMAC_STATUS0);
			if (val & MVPP2_GMAC_STATUS0_LINK_UP)
				link = true;
		}
	}

	if (port->phylink) {
		phylink_mac_change(port->phylink, link);
		goto handled;
	}

	if (!netif_running(dev) || !event)
		goto handled;

	if (link) {
		mvpp2_interrupts_enable(port);

		mvpp2_egress_enable(port);
		mvpp2_ingress_enable(port);
		netif_carrier_on(dev);
		netif_tx_wake_all_queues(dev);
	} else {
		netif_tx_stop_all_queues(dev);
		netif_carrier_off(dev);
		mvpp2_ingress_disable(port);
		mvpp2_egress_disable(port);

		mvpp2_interrupts_disable(port);
	}

handled:
	mvpp22_gop_unmask_irq(port);
	return IRQ_HANDLED;
}