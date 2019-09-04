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
struct mvpp2_port {scalar_t__ gop_id; scalar_t__ phy_interface; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP22_XLG_CTRL3_MACMODESELECT_10G ; 
 int /*<<< orphan*/  MVPP22_XLG_CTRL3_MACMODESELECT_GMAC ; 
 int /*<<< orphan*/  MVPP22_XLG_CTRL3_MACMODESELECT_MASK ; 
 scalar_t__ MVPP22_XLG_CTRL3_REG ; 
 scalar_t__ PHY_INTERFACE_MODE_10GKR ; 
 scalar_t__ PHY_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  mvpp22_comphy_init (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_gop_init (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_gmac_max_rx_size_set (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_xlg_max_rx_size_set (struct mvpp2_port*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvpp22_mode_reconfigure(struct mvpp2_port *port)
{
	u32 ctrl3;

	/* comphy reconfiguration */
	mvpp22_comphy_init(port);

	/* gop reconfiguration */
	mvpp22_gop_init(port);

	/* Only GOP port 0 has an XLG MAC */
	if (port->gop_id == 0) {
		ctrl3 = readl(port->base + MVPP22_XLG_CTRL3_REG);
		ctrl3 &= ~MVPP22_XLG_CTRL3_MACMODESELECT_MASK;

		if (port->phy_interface == PHY_INTERFACE_MODE_XAUI ||
		    port->phy_interface == PHY_INTERFACE_MODE_10GKR)
			ctrl3 |= MVPP22_XLG_CTRL3_MACMODESELECT_10G;
		else
			ctrl3 |= MVPP22_XLG_CTRL3_MACMODESELECT_GMAC;

		writel(ctrl3, port->base + MVPP22_XLG_CTRL3_REG);
	}

	if (port->gop_id == 0 &&
	    (port->phy_interface == PHY_INTERFACE_MODE_XAUI ||
	     port->phy_interface == PHY_INTERFACE_MODE_10GKR))
		mvpp2_xlg_max_rx_size_set(port);
	else
		mvpp2_gmac_max_rx_size_set(port);
}