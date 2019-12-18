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
struct pci_dev {int /*<<< orphan*/  is_hotplug_bridge; int /*<<< orphan*/  is_thunderbolt; } ;

/* Variables and functions */
#define  PCI_EXP_TYPE_DOWNSTREAM 130 
#define  PCI_EXP_TYPE_ROOT_PORT 129 
#define  PCI_EXP_TYPE_UPSTREAM 128 
 int /*<<< orphan*/  bridge_d3_blacklist ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int dmi_get_bios_year () ; 
 int /*<<< orphan*/  pci_bridge_d3_disable ; 
 int /*<<< orphan*/  pci_bridge_d3_force ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pciehp_is_native (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_pci_bridge_d3 (struct pci_dev*) ; 

bool pci_bridge_d3_possible(struct pci_dev *bridge)
{
	if (!pci_is_pcie(bridge))
		return false;

	switch (pci_pcie_type(bridge)) {
	case PCI_EXP_TYPE_ROOT_PORT:
	case PCI_EXP_TYPE_UPSTREAM:
	case PCI_EXP_TYPE_DOWNSTREAM:
		if (pci_bridge_d3_disable)
			return false;

		/*
		 * Hotplug ports handled by firmware in System Management Mode
		 * may not be put into D3 by the OS (Thunderbolt on non-Macs).
		 */
		if (bridge->is_hotplug_bridge && !pciehp_is_native(bridge))
			return false;

		if (pci_bridge_d3_force)
			return true;

		/* Even the oldest 2010 Thunderbolt controller supports D3. */
		if (bridge->is_thunderbolt)
			return true;

		/* Platform might know better if the bridge supports D3 */
		if (platform_pci_bridge_d3(bridge))
			return true;

		/*
		 * Hotplug ports handled natively by the OS were not validated
		 * by vendors for runtime D3 at least until 2018 because there
		 * was no OS support.
		 */
		if (bridge->is_hotplug_bridge)
			return false;

		if (dmi_check_system(bridge_d3_blacklist))
			return false;

		/*
		 * It should be safe to put PCIe ports from 2015 or newer
		 * to D3.
		 */
		if (dmi_get_bios_year() >= 2015)
			return true;
		break;
	}

	return false;
}