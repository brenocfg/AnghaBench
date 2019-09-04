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
struct mvpp2_port {scalar_t__ gop_id; scalar_t__ phy_interface; scalar_t__ base; } ;

/* Variables and functions */
 int MVPP22_XLG_CTRL0_MAC_RESET_DIS ; 
 int MVPP22_XLG_CTRL0_MIB_CNT_DIS ; 
 int MVPP22_XLG_CTRL0_PORT_EN ; 
 scalar_t__ MVPP22_XLG_CTRL0_REG ; 
 scalar_t__ MVPP2_GMAC_CTRL_0_REG ; 
 int MVPP2_GMAC_MIB_CNTR_EN_MASK ; 
 int MVPP2_GMAC_PORT_EN_MASK ; 
 scalar_t__ PHY_INTERFACE_MODE_10GKR ; 
 scalar_t__ PHY_INTERFACE_MODE_XAUI ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvpp2_port_enable(struct mvpp2_port *port)
{
	u32 val;

	/* Only GOP port 0 has an XLG MAC */
	if (port->gop_id == 0 &&
	    (port->phy_interface == PHY_INTERFACE_MODE_XAUI ||
	     port->phy_interface == PHY_INTERFACE_MODE_10GKR)) {
		val = readl(port->base + MVPP22_XLG_CTRL0_REG);
		val |= MVPP22_XLG_CTRL0_PORT_EN |
		       MVPP22_XLG_CTRL0_MAC_RESET_DIS;
		val &= ~MVPP22_XLG_CTRL0_MIB_CNT_DIS;
		writel(val, port->base + MVPP22_XLG_CTRL0_REG);
	} else {
		val = readl(port->base + MVPP2_GMAC_CTRL_0_REG);
		val |= MVPP2_GMAC_PORT_EN_MASK;
		val |= MVPP2_GMAC_MIB_CNTR_EN_MASK;
		writel(val, port->base + MVPP2_GMAC_CTRL_0_REG);
	}
}