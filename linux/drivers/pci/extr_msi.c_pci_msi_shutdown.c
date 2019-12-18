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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  irq; scalar_t__ msi_enabled; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_irq; int /*<<< orphan*/  multi_cap; } ;
struct msi_desc {TYPE_1__ msi_attrib; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pci_msi_desc_mask_irq (struct msi_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_msi_list (int /*<<< orphan*/ *) ; 
 struct msi_desc* first_pci_msi_entry (struct pci_dev*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_intx_for_msi (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_msi_enable ; 
 int /*<<< orphan*/  pci_msi_set_enable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcibios_alloc_irq (struct pci_dev*) ; 

__attribute__((used)) static void pci_msi_shutdown(struct pci_dev *dev)
{
	struct msi_desc *desc;
	u32 mask;

	if (!pci_msi_enable || !dev || !dev->msi_enabled)
		return;

	BUG_ON(list_empty(dev_to_msi_list(&dev->dev)));
	desc = first_pci_msi_entry(dev);

	pci_msi_set_enable(dev, 0);
	pci_intx_for_msi(dev, 1);
	dev->msi_enabled = 0;

	/* Return the device with MSI unmasked as initial states */
	mask = msi_mask(desc->msi_attrib.multi_cap);
	/* Keep cached state to be restored */
	__pci_msi_desc_mask_irq(desc, mask, ~mask);

	/* Restore dev->irq to its default pin-assertion IRQ */
	dev->irq = desc->msi_attrib.default_irq;
	pcibios_alloc_irq(dev);
}