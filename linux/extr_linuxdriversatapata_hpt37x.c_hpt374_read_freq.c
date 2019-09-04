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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {scalar_t__ devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int PCI_FUNC (scalar_t__) ; 
 int /*<<< orphan*/  inl (unsigned long) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static u32 hpt374_read_freq(struct pci_dev *pdev)
{
	u32 freq;
	unsigned long io_base = pci_resource_start(pdev, 4);

	if (PCI_FUNC(pdev->devfn) & 1) {
		struct pci_dev *pdev_0;

		pdev_0 = pci_get_slot(pdev->bus, pdev->devfn - 1);
		/* Someone hot plugged the controller on us ? */
		if (pdev_0 == NULL)
			return 0;
		io_base = pci_resource_start(pdev_0, 4);
		freq = inl(io_base + 0x90);
		pci_dev_put(pdev_0);
	} else
		freq = inl(io_base + 0x90);
	return freq;
}