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
struct tegra_pcie_soc {unsigned long afi_pex2_ctrl; } ;
struct tegra_pcie_port {int index; TYPE_1__* pcie; } ;
struct TYPE_2__ {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 unsigned long AFI_PEX0_CTRL ; 
 unsigned long AFI_PEX1_CTRL ; 

__attribute__((used)) static unsigned long tegra_pcie_port_get_pex_ctrl(struct tegra_pcie_port *port)
{
	const struct tegra_pcie_soc *soc = port->pcie->soc;
	unsigned long ret = 0;

	switch (port->index) {
	case 0:
		ret = AFI_PEX0_CTRL;
		break;

	case 1:
		ret = AFI_PEX1_CTRL;
		break;

	case 2:
		ret = soc->afi_pex2_ctrl;
		break;
	}

	return ret;
}