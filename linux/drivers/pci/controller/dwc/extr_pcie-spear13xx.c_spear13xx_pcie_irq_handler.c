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
struct spear13xx_pcie {struct dw_pcie* pci; struct pcie_app_reg* app_base; } ;
struct pcie_port {int dummy; } ;
struct pcie_app_reg {int /*<<< orphan*/  int_clr; int /*<<< orphan*/  int_sts; } ;
struct dw_pcie {struct pcie_port pp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int MSI_CTRL_INT ; 
 int /*<<< orphan*/  dw_handle_msi_irq (struct pcie_port*) ; 
 unsigned int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t spear13xx_pcie_irq_handler(int irq, void *arg)
{
	struct spear13xx_pcie *spear13xx_pcie = arg;
	struct pcie_app_reg *app_reg = spear13xx_pcie->app_base;
	struct dw_pcie *pci = spear13xx_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	unsigned int status;

	status = readl(&app_reg->int_sts);

	if (status & MSI_CTRL_INT) {
		BUG_ON(!IS_ENABLED(CONFIG_PCI_MSI));
		dw_handle_msi_irq(pp);
	}

	writel(status, &app_reg->int_clr);

	return IRQ_HANDLED;
}