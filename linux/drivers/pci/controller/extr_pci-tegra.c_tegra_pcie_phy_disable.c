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
struct tegra_pcie_soc {int /*<<< orphan*/  pads_pll_ctl; } ;
struct tegra_pcie {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PADS_CTL ; 
 int PADS_CTL_IDDQ_1L ; 
 int PADS_CTL_RX_DATA_EN_1L ; 
 int PADS_CTL_TX_DATA_EN_1L ; 
 int PADS_PLL_CTL_RST_B4SM ; 
 int pads_readl (struct tegra_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pads_writel (struct tegra_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_pcie_phy_disable(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	u32 value;

	/* disable TX/RX data */
	value = pads_readl(pcie, PADS_CTL);
	value &= ~(PADS_CTL_TX_DATA_EN_1L | PADS_CTL_RX_DATA_EN_1L);
	pads_writel(pcie, value, PADS_CTL);

	/* override IDDQ */
	value = pads_readl(pcie, PADS_CTL);
	value |= PADS_CTL_IDDQ_1L;
	pads_writel(pcie, value, PADS_CTL);

	/* reset PLL */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value &= ~PADS_PLL_CTL_RST_B4SM;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	usleep_range(20, 100);

	return 0;
}