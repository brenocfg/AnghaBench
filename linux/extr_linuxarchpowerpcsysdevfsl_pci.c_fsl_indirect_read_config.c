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
typedef  int /*<<< orphan*/  u32 ;
struct pci_controller {int /*<<< orphan*/  indirect_type; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_INDIRECT_TYPE_NO_PCIE_LINK ; 
 scalar_t__ fsl_pcie_check_link (struct pci_controller*) ; 
 int indirect_read_config (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 

__attribute__((used)) static int fsl_indirect_read_config(struct pci_bus *bus, unsigned int devfn,
				    int offset, int len, u32 *val)
{
	struct pci_controller *hose = pci_bus_to_host(bus);

	if (fsl_pcie_check_link(hose))
		hose->indirect_type |= PPC_INDIRECT_TYPE_NO_PCIE_LINK;
	else
		hose->indirect_type &= ~PPC_INDIRECT_TYPE_NO_PCIE_LINK;

	return indirect_read_config(bus, devfn, offset, len, val);
}