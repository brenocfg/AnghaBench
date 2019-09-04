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
struct mvpp2_port {scalar_t__ phy_interface; scalar_t__ gop_id; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MVPP22_GMAC_INT_MASK ; 
 int /*<<< orphan*/  MVPP22_GMAC_INT_MASK_LINK_STAT ; 
 scalar_t__ MVPP22_XLG_INT_MASK ; 
 int /*<<< orphan*/  MVPP22_XLG_INT_MASK_LINK ; 
 scalar_t__ PHY_INTERFACE_MODE_1000BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  mvpp22_gop_unmask_irq (struct mvpp2_port*) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvpp22_gop_setup_irq(struct mvpp2_port *port)
{
	u32 val;

	if (phy_interface_mode_is_rgmii(port->phy_interface) ||
	    port->phy_interface == PHY_INTERFACE_MODE_SGMII ||
	    port->phy_interface == PHY_INTERFACE_MODE_1000BASEX ||
	    port->phy_interface == PHY_INTERFACE_MODE_2500BASEX) {
		val = readl(port->base + MVPP22_GMAC_INT_MASK);
		val |= MVPP22_GMAC_INT_MASK_LINK_STAT;
		writel(val, port->base + MVPP22_GMAC_INT_MASK);
	}

	if (port->gop_id == 0) {
		val = readl(port->base + MVPP22_XLG_INT_MASK);
		val |= MVPP22_XLG_INT_MASK_LINK;
		writel(val, port->base + MVPP22_XLG_INT_MASK);
	}

	mvpp22_gop_unmask_irq(port);
}