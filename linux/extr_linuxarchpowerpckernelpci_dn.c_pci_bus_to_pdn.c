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
struct pci_dn {int dummy; } ;
struct pci_bus {struct pci_bus* parent; scalar_t__ self; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 struct device_node* pci_bus_to_OF_node (struct pci_bus*) ; 
 scalar_t__ pci_is_root_bus (struct pci_bus*) ; 

__attribute__((used)) static struct pci_dn *pci_bus_to_pdn(struct pci_bus *bus)
{
	struct pci_bus *pbus;
	struct device_node *dn;
	struct pci_dn *pdn;

	/*
	 * We probably have virtual bus which doesn't
	 * have associated bridge.
	 */
	pbus = bus;
	while (pbus) {
		if (pci_is_root_bus(pbus) || pbus->self)
			break;

		pbus = pbus->parent;
	}

	/*
	 * Except virtual bus, all PCI buses should
	 * have device nodes.
	 */
	dn = pci_bus_to_OF_node(pbus);
	pdn = dn ? PCI_DN(dn) : NULL;

	return pdn;
}