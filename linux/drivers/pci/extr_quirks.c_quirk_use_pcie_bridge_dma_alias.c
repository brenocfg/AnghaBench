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
struct pci_dev {scalar_t__ hdr_type; int /*<<< orphan*/  dev_flags; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEV_FLAG_PCIE_BRIDGE_ALIAS ; 
 scalar_t__ PCI_EXP_TYPE_PCI_BRIDGE ; 
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_is_root_bus (TYPE_1__*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

__attribute__((used)) static void quirk_use_pcie_bridge_dma_alias(struct pci_dev *pdev)
{
	if (!pci_is_root_bus(pdev->bus) &&
	    pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE &&
	    !pci_is_pcie(pdev) && pci_is_pcie(pdev->bus->self) &&
	    pci_pcie_type(pdev->bus->self) != PCI_EXP_TYPE_PCI_BRIDGE)
		pdev->dev_flags |= PCI_DEV_FLAG_PCIE_BRIDGE_ALIAS;
}