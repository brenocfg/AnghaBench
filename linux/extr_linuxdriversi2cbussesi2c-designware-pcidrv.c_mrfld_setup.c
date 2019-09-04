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
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct dw_pci_controller {int /*<<< orphan*/  bus_num; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrfld_setup(struct pci_dev *pdev, struct dw_pci_controller *c)
{
	/*
	 * On Intel Merrifield the user visible i2c busses are enumerated
	 * [1..7]. So, we add 1 to shift the default range. Besides that the
	 * first PCI slot provides 4 functions, that's why we have to add 0 to
	 * the first slot and 4 to the next one.
	 */
	switch (PCI_SLOT(pdev->devfn)) {
	case 8:
		c->bus_num = PCI_FUNC(pdev->devfn) + 0 + 1;
		return 0;
	case 9:
		c->bus_num = PCI_FUNC(pdev->devfn) + 4 + 1;
		return 0;
	}
	return -ENODEV;
}