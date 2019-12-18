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
struct tegra_pcie_dw {int dummy; } ;
struct pcie_port {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_INTR_EN_L0_0 ; 
 int /*<<< orphan*/  APPL_INTR_EN_L0_0_INT_INT_EN ; 
 int /*<<< orphan*/  APPL_INTR_EN_L0_0_SYS_INTR_EN ; 
 int /*<<< orphan*/  APPL_INTR_EN_L1_8_0 ; 
 int /*<<< orphan*/  APPL_INTR_EN_L1_8_AER_INT_EN ; 
 int /*<<< orphan*/  APPL_INTR_EN_L1_8_AUTO_BW_INT_EN ; 
 int /*<<< orphan*/  APPL_INTR_EN_L1_8_BW_MGT_INT_EN ; 
 int /*<<< orphan*/  APPL_INTR_EN_L1_8_INTX_EN ; 
 int /*<<< orphan*/  CONFIG_PCIEAER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_readl (struct tegra_pcie_dw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_writel (struct tegra_pcie_dw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct tegra_pcie_dw* to_tegra_pcie (struct dw_pcie*) ; 

__attribute__((used)) static void tegra_pcie_enable_legacy_interrupts(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val;

	/* Enable legacy interrupt generation */
	val = appl_readl(pcie, APPL_INTR_EN_L0_0);
	val |= APPL_INTR_EN_L0_0_SYS_INTR_EN;
	val |= APPL_INTR_EN_L0_0_INT_INT_EN;
	appl_writel(pcie, val, APPL_INTR_EN_L0_0);

	val = appl_readl(pcie, APPL_INTR_EN_L1_8_0);
	val |= APPL_INTR_EN_L1_8_INTX_EN;
	val |= APPL_INTR_EN_L1_8_AUTO_BW_INT_EN;
	val |= APPL_INTR_EN_L1_8_BW_MGT_INT_EN;
	if (IS_ENABLED(CONFIG_PCIEAER))
		val |= APPL_INTR_EN_L1_8_AER_INT_EN;
	appl_writel(pcie, val, APPL_INTR_EN_L1_8_0);
}