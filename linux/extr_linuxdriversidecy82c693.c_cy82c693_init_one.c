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
struct pci_device_id {int dummy; } ;
struct pci_dev {int class; scalar_t__ devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENODEV ; 
 int PCI_CLASS_STORAGE_IDE ; 
 int PCI_FUNC (scalar_t__) ; 
 int /*<<< orphan*/  cy82c693_chipset ; 
 int ide_pci_init_two (struct pci_dev*,struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cy82c693_init_one(struct pci_dev *dev,
			     const struct pci_device_id *id)
{
	struct pci_dev *dev2;
	int ret = -ENODEV;

	/* CY82C693 is more than only a IDE controller.
	   Function 1 is primary IDE channel, function 2 - secondary. */
	if ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE &&
	    PCI_FUNC(dev->devfn) == 1) {
		dev2 = pci_get_slot(dev->bus, dev->devfn + 1);
		ret = ide_pci_init_two(dev, dev2, &cy82c693_chipset, NULL);
		if (ret)
			pci_dev_put(dev2);
	}
	return ret;
}