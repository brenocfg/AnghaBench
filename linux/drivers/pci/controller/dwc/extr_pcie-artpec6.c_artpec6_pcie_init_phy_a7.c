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
struct dw_pcie {int /*<<< orphan*/  dev; } ;
struct artpec6_pcie {struct dw_pcie* pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOCCFG ; 
 int NOCCFG_ENABLE_CLK_PCIE ; 
 int NOCCFG_POWER_PCIE_IDLEREQ ; 
 int /*<<< orphan*/  PCIECFG ; 
 int PCIECFG_PCLK_ENABLE ; 
 int PCIECFG_REFCLKSEL ; 
 int PCIECFG_RISRCREN ; 
 int /*<<< orphan*/  PCIESTAT ; 
 int PCIESTAT_EXTREFCLK ; 
 int artpec6_pcie_readl (struct artpec6_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  artpec6_pcie_writel (struct artpec6_pcie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void artpec6_pcie_init_phy_a7(struct artpec6_pcie *artpec6_pcie)
{
	struct dw_pcie *pci = artpec6_pcie->pci;
	u32 val;
	bool extrefclk;

	/* Check if external reference clock is connected */
	val = artpec6_pcie_readl(artpec6_pcie, PCIESTAT);
	extrefclk = !!(val & PCIESTAT_EXTREFCLK);
	dev_dbg(pci->dev, "Using reference clock: %s\n",
		extrefclk ? "external" : "internal");

	val = artpec6_pcie_readl(artpec6_pcie, PCIECFG);
	val |=  PCIECFG_RISRCREN |	/* Receiver term. 50 Ohm */
		PCIECFG_PCLK_ENABLE;
	if (extrefclk)
		val |= PCIECFG_REFCLKSEL;
	else
		val &= ~PCIECFG_REFCLKSEL;
	artpec6_pcie_writel(artpec6_pcie, PCIECFG, val);
	usleep_range(10, 20);

	val = artpec6_pcie_readl(artpec6_pcie, NOCCFG);
	val |= NOCCFG_ENABLE_CLK_PCIE;
	artpec6_pcie_writel(artpec6_pcie, NOCCFG, val);
	usleep_range(20, 30);

	val = artpec6_pcie_readl(artpec6_pcie, NOCCFG);
	val &= ~NOCCFG_POWER_PCIE_IDLEREQ;
	artpec6_pcie_writel(artpec6_pcie, NOCCFG, val);
}