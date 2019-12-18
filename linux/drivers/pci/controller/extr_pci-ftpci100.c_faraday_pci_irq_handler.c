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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct faraday_pci {int /*<<< orphan*/  irqdomain; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  FARADAY_PCI_CTRL2 ; 
 unsigned int PCI_CTRL2_INTSTS_SHIFT ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  faraday_raw_pci_read_config (struct faraday_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct faraday_pci* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void faraday_pci_irq_handler(struct irq_desc *desc)
{
	struct faraday_pci *p = irq_desc_get_handler_data(desc);
	struct irq_chip *irqchip = irq_desc_get_chip(desc);
	unsigned int irq_stat, reg, i;

	faraday_raw_pci_read_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, &reg);
	irq_stat = reg >> PCI_CTRL2_INTSTS_SHIFT;

	chained_irq_enter(irqchip, desc);

	for (i = 0; i < 4; i++) {
		if ((irq_stat & BIT(i)) == 0)
			continue;
		generic_handle_irq(irq_find_mapping(p->irqdomain, i));
	}

	chained_irq_exit(irqchip, desc);
}