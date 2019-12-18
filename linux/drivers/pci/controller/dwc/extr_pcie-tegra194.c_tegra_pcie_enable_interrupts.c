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
struct tegra_pcie_dw {int dummy; } ;
struct pcie_port {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_INTR_STATUS_L0 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_0_0 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_1 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_10 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_11 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_13 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_14 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_15 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_17 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_2 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_3 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_6 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_7 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_8_0 ; 
 int /*<<< orphan*/  APPL_INTR_STATUS_L1_9 ; 
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appl_writel (struct tegra_pcie_dw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcie_enable_legacy_interrupts (struct pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_enable_msi_interrupts (struct pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_enable_system_interrupts (struct pcie_port*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct tegra_pcie_dw* to_tegra_pcie (struct dw_pcie*) ; 

__attribute__((used)) static void tegra_pcie_enable_interrupts(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct tegra_pcie_dw *pcie = to_tegra_pcie(pci);

	/* Clear interrupt statuses before enabling interrupts */
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L0);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_0_0);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_1);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_2);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_3);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_6);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_7);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_8_0);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_9);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_10);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_11);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_13);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_14);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_15);
	appl_writel(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_17);

	tegra_pcie_enable_system_interrupts(pp);
	tegra_pcie_enable_legacy_interrupts(pp);
	if (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_pcie_enable_msi_interrupts(pp);
}