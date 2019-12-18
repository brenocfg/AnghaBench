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
struct pci_dev {int class; struct pci_bus* subordinate; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
#define  PCI_CLASS_BRIDGE_CARDBUS 129 
#define  PCI_CLASS_BRIDGE_PCI 128 
 int /*<<< orphan*/  __pci_bus_assign_resources (struct pci_bus*,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_setup_bridge (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_setup_cardbus (struct pci_bus*) ; 
 int /*<<< orphan*/  pdev_assign_resources_sorted (struct pci_dev*,struct list_head*,struct list_head*) ; 

__attribute__((used)) static void __pci_bridge_assign_resources(const struct pci_dev *bridge,
					  struct list_head *add_head,
					  struct list_head *fail_head)
{
	struct pci_bus *b;

	pdev_assign_resources_sorted((struct pci_dev *)bridge,
					 add_head, fail_head);

	b = bridge->subordinate;
	if (!b)
		return;

	__pci_bus_assign_resources(b, add_head, fail_head);

	switch (bridge->class >> 8) {
	case PCI_CLASS_BRIDGE_PCI:
		pci_setup_bridge(b);
		break;

	case PCI_CLASS_BRIDGE_CARDBUS:
		pci_setup_cardbus(b);
		break;

	default:
		pci_info(bridge, "not setting up bridge for bus %04x:%02x\n",
			 pci_domain_nr(b), b->number);
		break;
	}
}