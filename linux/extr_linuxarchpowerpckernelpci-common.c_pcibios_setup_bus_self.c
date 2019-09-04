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
struct TYPE_3__ {int /*<<< orphan*/  (* dma_bus_setup ) (struct pci_bus*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct pci_bus {int /*<<< orphan*/ * self; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pcibios_fixup_bus ) (struct pci_bus*) ;} ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pcibios_fixup_bridge (struct pci_bus*) ; 
 TYPE_2__ ppc_md ; 
 int /*<<< orphan*/  stub1 (struct pci_bus*) ; 
 int /*<<< orphan*/  stub2 (struct pci_bus*) ; 

void pcibios_setup_bus_self(struct pci_bus *bus)
{
	struct pci_controller *phb;

	/* Fix up the bus resources for P2P bridges */
	if (bus->self != NULL)
		pcibios_fixup_bridge(bus);

	/* Platform specific bus fixups. This is currently only used
	 * by fsl_pci and I'm hoping to get rid of it at some point
	 */
	if (ppc_md.pcibios_fixup_bus)
		ppc_md.pcibios_fixup_bus(bus);

	/* Setup bus DMA mappings */
	phb = pci_bus_to_host(bus);
	if (phb->controller_ops.dma_bus_setup)
		phb->controller_ops.dma_bus_setup(bus);
}