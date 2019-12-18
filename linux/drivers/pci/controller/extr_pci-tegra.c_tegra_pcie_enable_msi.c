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
struct tegra_pcie_soc {int msi_base_shift; } ;
struct tegra_msi {int phys; } ;
struct tegra_pcie {struct tegra_msi msi; struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_INTR_MASK ; 
 int AFI_INTR_MASK_MSI_MASK ; 
 int /*<<< orphan*/  AFI_MSI_AXI_BAR_ST ; 
 int /*<<< orphan*/  AFI_MSI_BAR_SZ ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC0 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC1 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC2 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC3 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC4 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC5 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC6 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC7 ; 
 int /*<<< orphan*/  AFI_MSI_FPCI_BAR_ST ; 
 int afi_readl (struct tegra_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afi_writel (struct tegra_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_pcie_enable_msi(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	struct tegra_msi *msi = &pcie->msi;
	u32 reg;

	afi_writel(pcie, msi->phys >> soc->msi_base_shift, AFI_MSI_FPCI_BAR_ST);
	afi_writel(pcie, msi->phys, AFI_MSI_AXI_BAR_ST);
	/* this register is in 4K increments */
	afi_writel(pcie, 1, AFI_MSI_BAR_SZ);

	/* enable all MSI vectors */
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC0);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC1);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC2);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC3);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC4);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC5);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC6);
	afi_writel(pcie, 0xffffffff, AFI_MSI_EN_VEC7);

	/* and unmask the MSI interrupt */
	reg = afi_readl(pcie, AFI_INTR_MASK);
	reg |= AFI_INTR_MASK_MSI_MASK;
	afi_writel(pcie, reg, AFI_INTR_MASK);
}