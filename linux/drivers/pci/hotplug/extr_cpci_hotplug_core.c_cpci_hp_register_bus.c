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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct slot {int number; int /*<<< orphan*/  slot_list; TYPE_1__ hotplug_slot; int /*<<< orphan*/  devfn; struct pci_bus* bus; } ;
struct pci_bus {int number; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 int SLOT_NAME_SIZE ; 
 scalar_t__ controller ; 
 int /*<<< orphan*/  cpci_hotplug_slot_ops ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_rwsem ; 
 int pci_hp_register (TYPE_1__*,struct pci_bus*,int,char*) ; 
 int /*<<< orphan*/  slot_list ; 
 char* slot_name (struct slot*) ; 
 int /*<<< orphan*/  slots ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int
cpci_hp_register_bus(struct pci_bus *bus, u8 first, u8 last)
{
	struct slot *slot;
	char name[SLOT_NAME_SIZE];
	int status;
	int i;

	if (!(controller && bus))
		return -ENODEV;

	/*
	 * Create a structure for each slot, and register that slot
	 * with the pci_hotplug subsystem.
	 */
	for (i = first; i <= last; ++i) {
		slot = kzalloc(sizeof(struct slot), GFP_KERNEL);
		if (!slot) {
			status = -ENOMEM;
			goto error;
		}

		slot->bus = bus;
		slot->number = i;
		slot->devfn = PCI_DEVFN(i, 0);

		snprintf(name, SLOT_NAME_SIZE, "%02x:%02x", bus->number, i);

		slot->hotplug_slot.ops = &cpci_hotplug_slot_ops;

		dbg("registering slot %s", name);
		status = pci_hp_register(&slot->hotplug_slot, bus, i, name);
		if (status) {
			err("pci_hp_register failed with error %d", status);
			goto error_slot;
		}
		dbg("slot registered with name: %s", slot_name(slot));

		/* Add slot to our internal list */
		down_write(&list_rwsem);
		list_add(&slot->slot_list, &slot_list);
		slots++;
		up_write(&list_rwsem);
	}
	return 0;
error_slot:
	kfree(slot);
error:
	return status;
}