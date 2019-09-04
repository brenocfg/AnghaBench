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
struct device {int /*<<< orphan*/  fwnode; } ;
struct pci_bus {struct device dev; struct pci_bus* parent; } ;
struct acpi_iort_node {int dummy; } ;
struct TYPE_2__ {struct pci_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IORT_NODE_NAMED_COMPONENT ; 
 int /*<<< orphan*/  ACPI_IORT_NODE_PCI_ROOT_COMPLEX ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 struct acpi_iort_node* iort_get_iort_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iort_match_node_callback ; 
 struct acpi_iort_node* iort_scan_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  pci_is_root_bus (struct pci_bus*) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct acpi_iort_node *iort_find_dev_node(struct device *dev)
{
	struct pci_bus *pbus;

	if (!dev_is_pci(dev)) {
		struct acpi_iort_node *node;
		/*
		 * scan iort_fwnode_list to see if it's an iort platform
		 * device (such as SMMU, PMCG),its iort node already cached
		 * and associated with fwnode when iort platform devices
		 * were initialized.
		 */
		node = iort_get_iort_node(dev->fwnode);
		if (node)
			return node;

		/*
		 * if not, then it should be a platform device defined in
		 * DSDT/SSDT (with Named Component node in IORT)
		 */
		return iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
				      iort_match_node_callback, dev);
	}

	/* Find a PCI root bus */
	pbus = to_pci_dev(dev)->bus;
	while (!pci_is_root_bus(pbus))
		pbus = pbus->parent;

	return iort_scan_node(ACPI_IORT_NODE_PCI_ROOT_COMPLEX,
			      iort_match_node_callback, &pbus->dev);
}