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
struct pci_dev {int dummy; } ;
struct comedi_device {int /*<<< orphan*/ * mmio; scalar_t__ irq; int /*<<< orphan*/  ioenabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

void comedi_pci_detach(struct comedi_device *dev)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);

	if (!pcidev || !dev->ioenabled)
		return;

	if (dev->irq) {
		free_irq(dev->irq, dev);
		dev->irq = 0;
	}
	if (dev->mmio) {
		iounmap(dev->mmio);
		dev->mmio = NULL;
	}
	comedi_pci_disable(dev);
}