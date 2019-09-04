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
struct pci_dn {int /*<<< orphan*/  list; int /*<<< orphan*/  child_list; } ;
struct device_node {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct pci_dn*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

void pci_remove_device_node_info(struct device_node *dn)
{
	struct pci_dn *pdn = dn ? PCI_DN(dn) : NULL;
	struct device_node *parent;
#ifdef CONFIG_EEH
	struct eeh_dev *edev = pdn_to_eeh_dev(pdn);

	if (edev)
		edev->pdn = NULL;
#endif

	if (!pdn)
		return;

	WARN_ON(!list_empty(&pdn->child_list));
	list_del(&pdn->list);

	parent = of_get_parent(dn);
	if (parent)
		of_node_put(parent);

	dn->data = NULL;
	kfree(pdn);
}