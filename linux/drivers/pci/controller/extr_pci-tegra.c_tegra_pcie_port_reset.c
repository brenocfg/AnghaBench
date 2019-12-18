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
struct tegra_pcie_port {int /*<<< orphan*/  pcie; scalar_t__ reset_gpio; } ;

/* Variables and functions */
 unsigned long AFI_PEX_CTRL_RST ; 
 unsigned long afi_readl (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  afi_writel (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 unsigned long tegra_pcie_port_get_pex_ctrl (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tegra_pcie_port_reset(struct tegra_pcie_port *port)
{
	unsigned long ctrl = tegra_pcie_port_get_pex_ctrl(port);
	unsigned long value;

	/* pulse reset signal */
	if (port->reset_gpio) {
		gpiod_set_value(port->reset_gpio, 1);
	} else {
		value = afi_readl(port->pcie, ctrl);
		value &= ~AFI_PEX_CTRL_RST;
		afi_writel(port->pcie, value, ctrl);
	}

	usleep_range(1000, 2000);

	if (port->reset_gpio) {
		gpiod_set_value(port->reset_gpio, 0);
	} else {
		value = afi_readl(port->pcie, ctrl);
		value |= AFI_PEX_CTRL_RST;
		afi_writel(port->pcie, value, ctrl);
	}
}