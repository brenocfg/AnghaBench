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
typedef  int u8 ;
struct pci_dev {int class; } ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_PCI ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 int fsl_pcie_bus_fixup ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void quirk_fsl_pcie_early(struct pci_dev *dev)
{
	u8 hdr_type;

	/* if we aren't a PCIe don't bother */
	if (!pci_is_pcie(dev))
		return;

	/* if we aren't in host mode don't bother */
	pci_read_config_byte(dev, PCI_HEADER_TYPE, &hdr_type);
	if ((hdr_type & 0x7f) != PCI_HEADER_TYPE_BRIDGE)
		return;

	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
	fsl_pcie_bus_fixup = 1;
	return;
}