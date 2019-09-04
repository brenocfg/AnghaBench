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
struct ar2315_pci_ctrl {int /*<<< orphan*/  irq; int /*<<< orphan*/  domain; int /*<<< orphan*/  irq_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR2315_PCI_IER ; 
 int AR2315_PCI_IER_ENABLE ; 
 int /*<<< orphan*/  AR2315_PCI_IMR ; 
 int AR2315_PCI_INT_ABORT ; 
 int AR2315_PCI_INT_EXT ; 
 int /*<<< orphan*/  AR2315_PCI_IRQ_EXT ; 
 int /*<<< orphan*/  AR2315_PCI_ISR ; 
 int /*<<< orphan*/  ar2315_pci_irq_handler ; 
 int /*<<< orphan*/  ar2315_pci_reg_mask (struct ar2315_pci_ctrl*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ar2315_pci_reg_write (struct ar2315_pci_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar2315_pci_ctrl*) ; 

__attribute__((used)) static void ar2315_pci_irq_init(struct ar2315_pci_ctrl *apc)
{
	ar2315_pci_reg_mask(apc, AR2315_PCI_IER, AR2315_PCI_IER_ENABLE, 0);
	ar2315_pci_reg_mask(apc, AR2315_PCI_IMR, (AR2315_PCI_INT_ABORT |
			    AR2315_PCI_INT_EXT), 0);

	apc->irq_ext = irq_create_mapping(apc->domain, AR2315_PCI_IRQ_EXT);

	irq_set_chained_handler_and_data(apc->irq, ar2315_pci_irq_handler,
					 apc);

	/* Clear any pending Abort or external Interrupts
	 * and enable interrupt processing */
	ar2315_pci_reg_write(apc, AR2315_PCI_ISR, AR2315_PCI_INT_ABORT |
						  AR2315_PCI_INT_EXT);
	ar2315_pci_reg_mask(apc, AR2315_PCI_IER, 0, AR2315_PCI_IER_ENABLE);
}