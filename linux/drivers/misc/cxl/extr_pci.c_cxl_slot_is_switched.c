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
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int CXL_MAX_PCIEX_PARENT ; 
 int ENODEV ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_is_type (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int cxl_slot_is_switched(struct pci_dev *dev)
{
	struct device_node *np;
	int depth = 0;

	if (!(np = pci_device_to_OF_node(dev))) {
		pr_err("cxl: np = NULL\n");
		return -ENODEV;
	}
	of_node_get(np);
	while (np) {
		np = of_get_next_parent(np);
		if (!of_node_is_type(np, "pciex"))
			break;
		depth++;
	}
	of_node_put(np);
	return (depth > CXL_MAX_PCIEX_PARENT);
}