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
typedef  int u16 ;
struct pci_dev {int link_active_reporting; } ;
struct pci_bus {int max_bus_speed; void* cur_bus_speed; struct pci_dev* self; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 scalar_t__ PCI_AGP_COMMAND ; 
 scalar_t__ PCI_AGP_STATUS ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP3 ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_DLLLARC ; 
 int PCI_EXP_LNKCAP_SLS ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_133MHz_PCIX_266 ; 
 int PCI_SPEED_133MHz_PCIX_533 ; 
 int PCI_SPEED_133MHz_PCIX_ECC ; 
 int PCI_SPEED_66MHz_PCIX ; 
 scalar_t__ PCI_X_BRIDGE_SSTATUS ; 
 int PCI_X_SSTATUS_133MHZ ; 
 int PCI_X_SSTATUS_266MHZ ; 
 int PCI_X_SSTATUS_533MHZ ; 
 int PCI_X_SSTATUS_FREQ ; 
 int PCI_X_SSTATUS_V2 ; 
 int PCI_X_SSTATUS_VERS ; 
 void* agp_speed (int,int) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int* pcie_link_speed ; 
 int /*<<< orphan*/  pcie_update_link_speed (struct pci_bus*,int) ; 
 void** pcix_bus_speed ; 

__attribute__((used)) static void pci_set_bus_speed(struct pci_bus *bus)
{
	struct pci_dev *bridge = bus->self;
	int pos;

	pos = pci_find_capability(bridge, PCI_CAP_ID_AGP);
	if (!pos)
		pos = pci_find_capability(bridge, PCI_CAP_ID_AGP3);
	if (pos) {
		u32 agpstat, agpcmd;

		pci_read_config_dword(bridge, pos + PCI_AGP_STATUS, &agpstat);
		bus->max_bus_speed = agp_speed(agpstat & 8, agpstat & 7);

		pci_read_config_dword(bridge, pos + PCI_AGP_COMMAND, &agpcmd);
		bus->cur_bus_speed = agp_speed(agpstat & 8, agpcmd & 7);
	}

	pos = pci_find_capability(bridge, PCI_CAP_ID_PCIX);
	if (pos) {
		u16 status;
		enum pci_bus_speed max;

		pci_read_config_word(bridge, pos + PCI_X_BRIDGE_SSTATUS,
				     &status);

		if (status & PCI_X_SSTATUS_533MHZ) {
			max = PCI_SPEED_133MHz_PCIX_533;
		} else if (status & PCI_X_SSTATUS_266MHZ) {
			max = PCI_SPEED_133MHz_PCIX_266;
		} else if (status & PCI_X_SSTATUS_133MHZ) {
			if ((status & PCI_X_SSTATUS_VERS) == PCI_X_SSTATUS_V2)
				max = PCI_SPEED_133MHz_PCIX_ECC;
			else
				max = PCI_SPEED_133MHz_PCIX;
		} else {
			max = PCI_SPEED_66MHz_PCIX;
		}

		bus->max_bus_speed = max;
		bus->cur_bus_speed = pcix_bus_speed[
			(status & PCI_X_SSTATUS_FREQ) >> 6];

		return;
	}

	if (pci_is_pcie(bridge)) {
		u32 linkcap;
		u16 linksta;

		pcie_capability_read_dword(bridge, PCI_EXP_LNKCAP, &linkcap);
		bus->max_bus_speed = pcie_link_speed[linkcap & PCI_EXP_LNKCAP_SLS];
		bridge->link_active_reporting = !!(linkcap & PCI_EXP_LNKCAP_DLLLARC);

		pcie_capability_read_word(bridge, PCI_EXP_LNKSTA, &linksta);
		pcie_update_link_speed(bus, linksta);
	}
}