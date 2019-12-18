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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port {int dummy; } ;
struct exynos_pcie {TYPE_1__* mem_res; struct dw_pcie* pci; } ;
struct dw_pcie {struct pcie_port pp; } ;
struct TYPE_2__ {int /*<<< orphan*/  elbi_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MSI_ENABLE ; 
 int /*<<< orphan*/  PCIE_IRQ_EN_LEVEL ; 
 int /*<<< orphan*/  dw_pcie_msi_init (struct pcie_port*) ; 
 int /*<<< orphan*/  exynos_pcie_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pcie_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_pcie_msi_init(struct exynos_pcie *ep)
{
	struct dw_pcie *pci = ep->pci;
	struct pcie_port *pp = &pci->pp;
	u32 val;

	dw_pcie_msi_init(pp);

	/* enable MSI interrupt */
	val = exynos_pcie_readl(ep->mem_res->elbi_base, PCIE_IRQ_EN_LEVEL);
	val |= IRQ_MSI_ENABLE;
	exynos_pcie_writel(ep->mem_res->elbi_base, val, PCIE_IRQ_EN_LEVEL);
}