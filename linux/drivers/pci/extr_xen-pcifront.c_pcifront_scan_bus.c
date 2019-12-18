#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcifront_device {TYPE_1__* xdev; } ;
struct pci_dev {int dummy; } ;
struct pci_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (struct pci_bus*,unsigned int) ; 
 struct pci_dev* pci_scan_single_device (struct pci_bus*,unsigned int) ; 

__attribute__((used)) static int pcifront_scan_bus(struct pcifront_device *pdev,
				unsigned int domain, unsigned int bus,
				struct pci_bus *b)
{
	struct pci_dev *d;
	unsigned int devfn;

	/* Scan the bus for functions and add.
	 * We omit handling of PCI bridge attachment because pciback prevents
	 * bridges from being exported.
	 */
	for (devfn = 0; devfn < 0x100; devfn++) {
		d = pci_get_slot(b, devfn);
		if (d) {
			/* Device is already known. */
			pci_dev_put(d);
			continue;
		}

		d = pci_scan_single_device(b, devfn);
		if (d)
			dev_info(&pdev->xdev->dev, "New device on "
				 "%04x:%02x:%02x.%d found.\n", domain, bus,
				 PCI_SLOT(devfn), PCI_FUNC(devfn));
	}

	return 0;
}