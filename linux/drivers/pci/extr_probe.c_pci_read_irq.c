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
struct pci_dev {unsigned char pin; unsigned char irq; scalar_t__ is_virtfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  PCI_INTERRUPT_PIN ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void pci_read_irq(struct pci_dev *dev)
{
	unsigned char irq;

	/* VFs are not allowed to use INTx, so skip the config reads */
	if (dev->is_virtfn) {
		dev->pin = 0;
		dev->irq = 0;
		return;
	}

	pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &irq);
	dev->pin = irq;
	if (irq)
		pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
	dev->irq = irq;
}