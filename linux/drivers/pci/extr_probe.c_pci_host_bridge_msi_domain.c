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
struct pci_bus {int dummy; } ;
struct irq_domain {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_PCI_MSI ; 
 struct irq_domain* irq_find_matching_fwnode (struct fwnode_handle*,int /*<<< orphan*/ ) ; 
 struct irq_domain* pci_host_bridge_acpi_msi_domain (struct pci_bus*) ; 
 struct irq_domain* pci_host_bridge_of_msi_domain (struct pci_bus*) ; 
 struct fwnode_handle* pci_root_bus_fwnode (struct pci_bus*) ; 

__attribute__((used)) static struct irq_domain *pci_host_bridge_msi_domain(struct pci_bus *bus)
{
	struct irq_domain *d;

	/*
	 * Any firmware interface that can resolve the msi_domain
	 * should be called from here.
	 */
	d = pci_host_bridge_of_msi_domain(bus);
	if (!d)
		d = pci_host_bridge_acpi_msi_domain(bus);

#ifdef CONFIG_PCI_MSI_IRQ_DOMAIN
	/*
	 * If no IRQ domain was found via the OF tree, try looking it up
	 * directly through the fwnode_handle.
	 */
	if (!d) {
		struct fwnode_handle *fwnode = pci_root_bus_fwnode(bus);

		if (fwnode)
			d = irq_find_matching_fwnode(fwnode,
						     DOMAIN_BUS_PCI_MSI);
	}
#endif

	return d;
}