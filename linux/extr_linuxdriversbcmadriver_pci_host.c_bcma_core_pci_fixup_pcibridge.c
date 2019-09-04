#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_PCI_BAR1_CONTROL ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ bcma_core_pci_hostmode_read_config ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcibios_enable_device (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_core_pci_fixup_pcibridge(struct pci_dev *dev)
{
	if (dev->bus->ops->read != bcma_core_pci_hostmode_read_config) {
		/* This is not a device on the PCI-core bridge. */
		return;
	}
	if (PCI_SLOT(dev->devfn) != 0)
		return;

	pr_info("PCI: Fixing up bridge %s\n", pci_name(dev));

	/* Enable PCI bridge bus mastering and memory space */
	pci_set_master(dev);
	if (pcibios_enable_device(dev, ~0) < 0) {
		pr_err("PCI: BCMA bridge enable failed\n");
		return;
	}

	/* Enable PCI bridge BAR1 prefetch and burst */
	pci_write_config_dword(dev, BCMA_PCI_BAR1_CONTROL, 3);
}