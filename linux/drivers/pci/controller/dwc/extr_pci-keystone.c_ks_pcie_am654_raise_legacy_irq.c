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
typedef  int u8 ;
struct keystone_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_ENABLE ; 
 int /*<<< orphan*/  PCIE_EP_IRQ_CLR ; 
 int /*<<< orphan*/  PCIE_EP_IRQ_SET ; 
 int /*<<< orphan*/  PCIE_LEGACY_IRQ_ENABLE_CLR (int) ; 
 int /*<<< orphan*/  PCIE_LEGACY_IRQ_ENABLE_SET (int) ; 
 int /*<<< orphan*/  PCI_INTERRUPT_PIN ; 
 int dw_pcie_readb_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_pcie_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void ks_pcie_am654_raise_legacy_irq(struct keystone_pcie *ks_pcie)
{
	struct dw_pcie *pci = ks_pcie->pci;
	u8 int_pin;

	int_pin = dw_pcie_readb_dbi(pci, PCI_INTERRUPT_PIN);
	if (int_pin == 0 || int_pin > 4)
		return;

	ks_pcie_app_writel(ks_pcie, PCIE_LEGACY_IRQ_ENABLE_SET(int_pin),
			   INT_ENABLE);
	ks_pcie_app_writel(ks_pcie, PCIE_EP_IRQ_SET, INT_ENABLE);
	mdelay(1);
	ks_pcie_app_writel(ks_pcie, PCIE_EP_IRQ_CLR, INT_ENABLE);
	ks_pcie_app_writel(ks_pcie, PCIE_LEGACY_IRQ_ENABLE_CLR(int_pin),
			   INT_ENABLE);
}