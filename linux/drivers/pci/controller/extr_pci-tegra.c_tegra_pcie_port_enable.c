#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ enable; } ;
struct tegra_pcie_soc {TYPE_1__ ectl; scalar_t__ force_pca_enable; scalar_t__ has_pex_clkreq_en; } ;
struct tegra_pcie_port {scalar_t__ base; TYPE_2__* pcie; } ;
struct TYPE_5__ {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 unsigned long AFI_PEX_CTRL_CLKREQ_EN ; 
 unsigned long AFI_PEX_CTRL_OVERRIDE_EN ; 
 unsigned long AFI_PEX_CTRL_REFCLK_EN ; 
 scalar_t__ RP_VEND_CTL2 ; 
 unsigned long RP_VEND_CTL2_PCA_ENABLE ; 
 unsigned long afi_readl (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  afi_writel (TYPE_2__*,unsigned long,unsigned long) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  tegra_pcie_apply_sw_fixup (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_enable_rp_features (struct tegra_pcie_port*) ; 
 unsigned long tegra_pcie_port_get_pex_ctrl (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_port_reset (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_program_ectl_settings (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void tegra_pcie_port_enable(struct tegra_pcie_port *port)
{
	unsigned long ctrl = tegra_pcie_port_get_pex_ctrl(port);
	const struct tegra_pcie_soc *soc = port->pcie->soc;
	unsigned long value;

	/* enable reference clock */
	value = afi_readl(port->pcie, ctrl);
	value |= AFI_PEX_CTRL_REFCLK_EN;

	if (soc->has_pex_clkreq_en)
		value |= AFI_PEX_CTRL_CLKREQ_EN;

	value |= AFI_PEX_CTRL_OVERRIDE_EN;

	afi_writel(port->pcie, value, ctrl);

	tegra_pcie_port_reset(port);

	if (soc->force_pca_enable) {
		value = readl(port->base + RP_VEND_CTL2);
		value |= RP_VEND_CTL2_PCA_ENABLE;
		writel(value, port->base + RP_VEND_CTL2);
	}

	tegra_pcie_enable_rp_features(port);

	if (soc->ectl.enable)
		tegra_pcie_program_ectl_settings(port);

	tegra_pcie_apply_sw_fixup(port);
}