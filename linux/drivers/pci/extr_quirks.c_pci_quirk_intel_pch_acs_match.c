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
struct pci_dev {scalar_t__ device; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 scalar_t__* pci_quirk_intel_pch_acs_ids ; 

__attribute__((used)) static bool pci_quirk_intel_pch_acs_match(struct pci_dev *dev)
{
	int i;

	/* Filter out a few obvious non-matches first */
	if (!pci_is_pcie(dev) || pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		return false;

	for (i = 0; i < ARRAY_SIZE(pci_quirk_intel_pch_acs_ids); i++)
		if (pci_quirk_intel_pch_acs_ids[i] == dev->device)
			return true;

	return false;
}