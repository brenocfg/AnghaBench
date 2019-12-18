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
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_set_vpd_size (struct pci_dev*,size_t) ; 

__attribute__((used)) static int pci_vpd_f0_set_size(struct pci_dev *dev, size_t len)
{
	struct pci_dev *tdev = pci_get_slot(dev->bus,
					    PCI_DEVFN(PCI_SLOT(dev->devfn), 0));
	int ret;

	if (!tdev)
		return -ENODEV;

	ret = pci_set_vpd_size(tdev, len);
	pci_dev_put(tdev);
	return ret;
}