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
typedef  scalar_t__ u8 ;
struct pci_dev {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_LEVEL_LOW ; 
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  PCI_INTERRUPT_PIN ; 
 int irq_create_mapping (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  irq_set_irq_type (int,int /*<<< orphan*/ ) ; 
 int of_irq_parse_and_map_pci (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_name (struct pci_dev*) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int pci_read_irq_line(struct pci_dev *pci_dev)
{
	int virq;

	pr_debug("PCI: Try to map irq for %s...\n", pci_name(pci_dev));

	/* Try to get a mapping from the device-tree */
	virq = of_irq_parse_and_map_pci(pci_dev, 0, 0);
	if (virq <= 0) {
		u8 line, pin;

		/* If that fails, lets fallback to what is in the config
		 * space and map that through the default controller. We
		 * also set the type to level low since that's what PCI
		 * interrupts are. If your platform does differently, then
		 * either provide a proper interrupt tree or don't use this
		 * function.
		 */
		if (pci_read_config_byte(pci_dev, PCI_INTERRUPT_PIN, &pin))
			return -1;
		if (pin == 0)
			return -1;
		if (pci_read_config_byte(pci_dev, PCI_INTERRUPT_LINE, &line) ||
		    line == 0xff || line == 0) {
			return -1;
		}
		pr_debug(" No map ! Using line %d (pin %d) from PCI config\n",
			 line, pin);

		virq = irq_create_mapping(NULL, line);
		if (virq)
			irq_set_irq_type(virq, IRQ_TYPE_LEVEL_LOW);
	}

	if (!virq) {
		pr_debug(" Failed to map !\n");
		return -1;
	}

	pr_debug(" Mapped to linux irq %d\n", virq);

	pci_dev->irq = virq;

	return 0;
}