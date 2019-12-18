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
typedef  int u32 ;
struct pci_host_bridge {int native_pcie_hotplug; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HOTPLUG_PCI_PCIE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_EXP_SLTCAP ; 
 int PCI_EXP_SLTCAP_HPC ; 
 struct pci_host_bridge* pci_find_host_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pcie_ports_native ; 

bool pciehp_is_native(struct pci_dev *bridge)
{
	const struct pci_host_bridge *host;
	u32 slot_cap;

	if (!IS_ENABLED(CONFIG_HOTPLUG_PCI_PCIE))
		return false;

	pcie_capability_read_dword(bridge, PCI_EXP_SLTCAP, &slot_cap);
	if (!(slot_cap & PCI_EXP_SLTCAP_HPC))
		return false;

	if (pcie_ports_native)
		return true;

	host = pci_find_host_bridge(bridge->bus);
	return host->native_pcie_hotplug;
}