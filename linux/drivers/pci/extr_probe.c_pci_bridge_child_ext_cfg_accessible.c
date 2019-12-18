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
typedef  int u32 ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int bus_flags; } ;

/* Variables and functions */
 int PCI_BUS_FLAGS_NO_EXTCFG ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 scalar_t__ PCI_EXP_TYPE_DOWNSTREAM ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ PCI_EXP_TYPE_UPSTREAM ; 
 scalar_t__ PCI_X_STATUS ; 
 int PCI_X_STATUS_266MHZ ; 
 int PCI_X_STATUS_533MHZ ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static bool pci_bridge_child_ext_cfg_accessible(struct pci_dev *bridge)
{
	int pos;
	u32 status;

	/*
	 * If extended config space isn't accessible on a bridge's primary
	 * bus, we certainly can't access it on the secondary bus.
	 */
	if (bridge->bus->bus_flags & PCI_BUS_FLAGS_NO_EXTCFG)
		return false;

	/*
	 * PCIe Root Ports and switch ports are PCIe on both sides, so if
	 * extended config space is accessible on the primary, it's also
	 * accessible on the secondary.
	 */
	if (pci_is_pcie(bridge) &&
	    (pci_pcie_type(bridge) == PCI_EXP_TYPE_ROOT_PORT ||
	     pci_pcie_type(bridge) == PCI_EXP_TYPE_UPSTREAM ||
	     pci_pcie_type(bridge) == PCI_EXP_TYPE_DOWNSTREAM))
		return true;

	/*
	 * For the other bridge types:
	 *   - PCI-to-PCI bridges
	 *   - PCIe-to-PCI/PCI-X forward bridges
	 *   - PCI/PCI-X-to-PCIe reverse bridges
	 * extended config space on the secondary side is only accessible
	 * if the bridge supports PCI-X Mode 2.
	 */
	pos = pci_find_capability(bridge, PCI_CAP_ID_PCIX);
	if (!pos)
		return false;

	pci_read_config_dword(bridge, pos + PCI_X_STATUS, &status);
	return status & (PCI_X_STATUS_266MHZ | PCI_X_STATUS_533MHZ);
}