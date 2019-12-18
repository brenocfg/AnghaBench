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
struct keystone_pcie {int /*<<< orphan*/  legacy_irq_domain; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_EOI ; 
 int /*<<< orphan*/  IRQ_STATUS (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int ks_pcie_app_readl (struct keystone_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_pcie_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ks_pcie_handle_legacy_irq(struct keystone_pcie *ks_pcie,
				      int offset)
{
	struct dw_pcie *pci = ks_pcie->pci;
	struct device *dev = pci->dev;
	u32 pending;
	int virq;

	pending = ks_pcie_app_readl(ks_pcie, IRQ_STATUS(offset));

	if (BIT(0) & pending) {
		virq = irq_linear_revmap(ks_pcie->legacy_irq_domain, offset);
		dev_dbg(dev, ": irq: irq_offset %d, virq %d\n", offset, virq);
		generic_handle_irq(virq);
	}

	/* EOI the INTx interrupt */
	ks_pcie_app_writel(ks_pcie, IRQ_EOI, offset);
}