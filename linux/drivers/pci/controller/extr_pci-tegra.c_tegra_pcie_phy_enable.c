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
struct tegra_pcie_soc {int tx_ref_sel; int /*<<< orphan*/  pads_pll_ctl; } ;
struct tegra_pcie {struct tegra_pcie_soc* soc; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PADS_CTL ; 
 int PADS_CTL_IDDQ_1L ; 
 int PADS_CTL_RX_DATA_EN_1L ; 
 int /*<<< orphan*/  PADS_CTL_SEL ; 
 int PADS_CTL_TX_DATA_EN_1L ; 
 int PADS_PLL_CTL_REFCLK_INTERNAL_CML ; 
 int PADS_PLL_CTL_REFCLK_MASK ; 
 int PADS_PLL_CTL_RST_B4SM ; 
 int PADS_PLL_CTL_TXCLKREF_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int pads_readl (struct tegra_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pads_writel (struct tegra_pcie*,int,int /*<<< orphan*/ ) ; 
 int tegra_pcie_pll_wait (struct tegra_pcie*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_pcie_phy_enable(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;
	const struct tegra_pcie_soc *soc = pcie->soc;
	u32 value;
	int err;

	/* initialize internal PHY, enable up to 16 PCIE lanes */
	pads_writel(pcie, 0x0, PADS_CTL_SEL);

	/* override IDDQ to 1 on all 4 lanes */
	value = pads_readl(pcie, PADS_CTL);
	value |= PADS_CTL_IDDQ_1L;
	pads_writel(pcie, value, PADS_CTL);

	/*
	 * Set up PHY PLL inputs select PLLE output as refclock,
	 * set TX ref sel to div10 (not div5).
	 */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value &= ~(PADS_PLL_CTL_REFCLK_MASK | PADS_PLL_CTL_TXCLKREF_MASK);
	value |= PADS_PLL_CTL_REFCLK_INTERNAL_CML | soc->tx_ref_sel;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	/* reset PLL */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value &= ~PADS_PLL_CTL_RST_B4SM;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	usleep_range(20, 100);

	/* take PLL out of reset  */
	value = pads_readl(pcie, soc->pads_pll_ctl);
	value |= PADS_PLL_CTL_RST_B4SM;
	pads_writel(pcie, value, soc->pads_pll_ctl);

	/* wait for the PLL to lock */
	err = tegra_pcie_pll_wait(pcie, 500);
	if (err < 0) {
		dev_err(dev, "PLL failed to lock: %d\n", err);
		return err;
	}

	/* turn off IDDQ override */
	value = pads_readl(pcie, PADS_CTL);
	value &= ~PADS_CTL_IDDQ_1L;
	pads_writel(pcie, value, PADS_CTL);

	/* enable TX/RX data */
	value = pads_readl(pcie, PADS_CTL);
	value |= PADS_CTL_TX_DATA_EN_1L | PADS_CTL_RX_DATA_EN_1L;
	pads_writel(pcie, value, PADS_CTL);

	return 0;
}