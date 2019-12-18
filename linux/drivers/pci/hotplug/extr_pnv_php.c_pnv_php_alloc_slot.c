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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct pnv_php_slot {int slot_no; int power_state_check; int /*<<< orphan*/  link; int /*<<< orphan*/  children; TYPE_1__ slot; int /*<<< orphan*/  id; struct pci_bus* bus; int /*<<< orphan*/  pdev; struct device_node* dn; int /*<<< orphan*/  state; int /*<<< orphan*/  kref; int /*<<< orphan*/  name; } ;
struct pci_bus {int /*<<< orphan*/  self; } ;
struct device_node {scalar_t__ child; } ;
struct TYPE_4__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* PCI_DN (scalar_t__) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PNV_PHP_STATE_INITIALIZED ; 
 int /*<<< orphan*/  kfree (struct pnv_php_slot*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct pnv_php_slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 struct pci_bus* pci_find_bus_by_node (struct device_node*) ; 
 int /*<<< orphan*/  php_slot_ops ; 
 scalar_t__ pnv_pci_get_slot_id (struct device_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pnv_php_slot *pnv_php_alloc_slot(struct device_node *dn)
{
	struct pnv_php_slot *php_slot;
	struct pci_bus *bus;
	const char *label;
	uint64_t id;
	int ret;

	ret = of_property_read_string(dn, "ibm,slot-label", &label);
	if (ret)
		return NULL;

	if (pnv_pci_get_slot_id(dn, &id))
		return NULL;

	bus = pci_find_bus_by_node(dn);
	if (!bus)
		return NULL;

	php_slot = kzalloc(sizeof(*php_slot), GFP_KERNEL);
	if (!php_slot)
		return NULL;

	php_slot->name = kstrdup(label, GFP_KERNEL);
	if (!php_slot->name) {
		kfree(php_slot);
		return NULL;
	}

	if (dn->child && PCI_DN(dn->child))
		php_slot->slot_no = PCI_SLOT(PCI_DN(dn->child)->devfn);
	else
		php_slot->slot_no = -1;   /* Placeholder slot */

	kref_init(&php_slot->kref);
	php_slot->state	                = PNV_PHP_STATE_INITIALIZED;
	php_slot->dn	                = dn;
	php_slot->pdev	                = bus->self;
	php_slot->bus	                = bus;
	php_slot->id	                = id;
	php_slot->power_state_check     = false;
	php_slot->slot.ops              = &php_slot_ops;

	INIT_LIST_HEAD(&php_slot->children);
	INIT_LIST_HEAD(&php_slot->link);

	return php_slot;
}