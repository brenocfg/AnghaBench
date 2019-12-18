#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_pcie_port {scalar_t__ base; int /*<<< orphan*/  index; TYPE_1__* pcie; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ RP_LINK_CONTROL_STATUS ; 
 unsigned long RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE ; 
 scalar_t__ RP_PRIV_MISC ; 
 unsigned long RP_PRIV_MISC_PRSNT_MAP_EP_ABSNT ; 
 unsigned long RP_PRIV_MISC_PRSNT_MAP_EP_PRSNT ; 
 scalar_t__ RP_VEND_XP ; 
 unsigned long RP_VEND_XP_DL_UP ; 
 unsigned int TEGRA_PCIE_LINKUP_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  tegra_pcie_port_reset (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static bool tegra_pcie_port_check_link(struct tegra_pcie_port *port)
{
	struct device *dev = port->pcie->dev;
	unsigned int retries = 3;
	unsigned long value;

	/* override presence detection */
	value = readl(port->base + RP_PRIV_MISC);
	value &= ~RP_PRIV_MISC_PRSNT_MAP_EP_ABSNT;
	value |= RP_PRIV_MISC_PRSNT_MAP_EP_PRSNT;
	writel(value, port->base + RP_PRIV_MISC);

	do {
		unsigned int timeout = TEGRA_PCIE_LINKUP_TIMEOUT;

		do {
			value = readl(port->base + RP_VEND_XP);

			if (value & RP_VEND_XP_DL_UP)
				break;

			usleep_range(1000, 2000);
		} while (--timeout);

		if (!timeout) {
			dev_dbg(dev, "link %u down, retrying\n", port->index);
			goto retry;
		}

		timeout = TEGRA_PCIE_LINKUP_TIMEOUT;

		do {
			value = readl(port->base + RP_LINK_CONTROL_STATUS);

			if (value & RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE)
				return true;

			usleep_range(1000, 2000);
		} while (--timeout);

retry:
		tegra_pcie_port_reset(port);
	} while (--retries);

	return false;
}