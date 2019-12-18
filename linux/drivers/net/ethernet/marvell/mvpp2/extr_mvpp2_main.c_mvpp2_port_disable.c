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
struct mvpp2_port {scalar_t__ gop_id; scalar_t__ base; int /*<<< orphan*/  phy_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP22_XLG_CTRL0_PORT_EN ; 
 scalar_t__ MVPP22_XLG_CTRL0_REG ; 
 scalar_t__ MVPP2_GMAC_CTRL_0_REG ; 
 int /*<<< orphan*/  MVPP2_GMAC_PORT_EN_MASK ; 
 scalar_t__ mvpp2_is_xlg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvpp2_port_disable(struct mvpp2_port *port)
{
	u32 val;

	/* Only GOP port 0 has an XLG MAC */
	if (port->gop_id == 0 && mvpp2_is_xlg(port->phy_interface)) {
		val = readl(port->base + MVPP22_XLG_CTRL0_REG);
		val &= ~MVPP22_XLG_CTRL0_PORT_EN;
		writel(val, port->base + MVPP22_XLG_CTRL0_REG);
	}

	val = readl(port->base + MVPP2_GMAC_CTRL_0_REG);
	val &= ~(MVPP2_GMAC_PORT_EN_MASK);
	writel(val, port->base + MVPP2_GMAC_CTRL_0_REG);
}