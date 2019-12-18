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
typedef  int uint16_t ;
struct pnv_php_slot {scalar_t__ irq; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  pci_bridge_secondary_bus_reset (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int pnv_php_reset_slot(struct hotplug_slot *slot, int probe)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	struct pci_dev *bridge = php_slot->pdev;
	uint16_t sts;

	/*
	 * The CAPI folks want pnv_php to drive OpenCAPI slots
	 * which don't have a bridge. Only claim to support
	 * reset_slot() if we have a bridge device (for now...)
	 */
	if (probe)
		return !bridge;

	/* mask our interrupt while resetting the bridge */
	if (php_slot->irq > 0)
		disable_irq(php_slot->irq);

	pci_bridge_secondary_bus_reset(bridge);

	/* clear any state changes that happened due to the reset */
	pcie_capability_read_word(php_slot->pdev, PCI_EXP_SLTSTA, &sts);
	sts &= (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC);
	pcie_capability_write_word(php_slot->pdev, PCI_EXP_SLTSTA, sts);

	if (php_slot->irq > 0)
		enable_irq(php_slot->irq);

	return 0;
}