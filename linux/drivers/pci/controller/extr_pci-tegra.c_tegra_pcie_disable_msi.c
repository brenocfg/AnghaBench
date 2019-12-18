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
struct tegra_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_INTR_MASK ; 
 int /*<<< orphan*/  AFI_INTR_MASK_MSI_MASK ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC0 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC1 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC2 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC3 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC4 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC5 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC6 ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC7 ; 
 int /*<<< orphan*/  afi_readl (struct tegra_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afi_writel (struct tegra_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pcie_disable_msi(struct tegra_pcie *pcie)
{
	u32 value;

	/* mask the MSI interrupt */
	value = afi_readl(pcie, AFI_INTR_MASK);
	value &= ~AFI_INTR_MASK_MSI_MASK;
	afi_writel(pcie, value, AFI_INTR_MASK);

	/* disable all MSI vectors */
	afi_writel(pcie, 0, AFI_MSI_EN_VEC0);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC1);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC2);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC3);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC4);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC5);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC6);
	afi_writel(pcie, 0, AFI_MSI_EN_VEC7);

	return 0;
}