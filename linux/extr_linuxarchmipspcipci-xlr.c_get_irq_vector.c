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

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int PIC_PCIX_IRQ ; 
 int /*<<< orphan*/  nlm_chip_is_xls () ; 
 int nlm_pci_link_to_irq (int) ; 
 struct pci_dev* xls_get_pcie_link (struct pci_dev const*) ; 

__attribute__((used)) static int get_irq_vector(const struct pci_dev *dev)
{
	struct pci_dev *lnk;
	int link;

	if (!nlm_chip_is_xls())
		return	PIC_PCIX_IRQ;	/* for XLR just one IRQ */

	lnk = xls_get_pcie_link(dev);
	if (lnk == NULL)
		return 0;

	link = PCI_SLOT(lnk->devfn);
	return nlm_pci_link_to_irq(link);
}