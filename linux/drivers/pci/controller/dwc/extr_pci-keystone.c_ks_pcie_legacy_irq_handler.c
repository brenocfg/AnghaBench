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
typedef  scalar_t__ u32 ;
struct keystone_pcie {scalar_t__* legacy_host_irqs; struct dw_pcie* pci; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct keystone_pcie* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  ks_pcie_handle_legacy_irq (struct keystone_pcie*,scalar_t__) ; 

__attribute__((used)) static void ks_pcie_legacy_irq_handler(struct irq_desc *desc)
{
	unsigned int irq = irq_desc_get_irq(desc);
	struct keystone_pcie *ks_pcie = irq_desc_get_handler_data(desc);
	struct dw_pcie *pci = ks_pcie->pci;
	struct device *dev = pci->dev;
	u32 irq_offset = irq - ks_pcie->legacy_host_irqs[0];
	struct irq_chip *chip = irq_desc_get_chip(desc);

	dev_dbg(dev, ": Handling legacy irq %d\n", irq);

	/*
	 * The chained irq handler installation would have replaced normal
	 * interrupt driver handler so we need to take care of mask/unmask and
	 * ack operation.
	 */
	chained_irq_enter(chip, desc);
	ks_pcie_handle_legacy_irq(ks_pcie, irq_offset);
	chained_irq_exit(chip, desc);
}