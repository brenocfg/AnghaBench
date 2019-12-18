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
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct slot {unsigned int sun; TYPE_1__ hotplug_slot; struct acpiphp_slot* acpi_slot; } ;
struct acpiphp_slot {int /*<<< orphan*/  device; int /*<<< orphan*/  bus; struct slot* slot; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  acpi_hotplug_slot_ops ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pci_hp_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

int acpiphp_register_hotplug_slot(struct acpiphp_slot *acpiphp_slot,
				  unsigned int sun)
{
	struct slot *slot;
	int retval = -ENOMEM;
	char name[SLOT_NAME_SIZE];

	slot = kzalloc(sizeof(*slot), GFP_KERNEL);
	if (!slot)
		goto error;

	slot->hotplug_slot.ops = &acpi_hotplug_slot_ops;

	slot->acpi_slot = acpiphp_slot;

	acpiphp_slot->slot = slot;
	slot->sun = sun;
	snprintf(name, SLOT_NAME_SIZE, "%u", sun);

	retval = pci_hp_register(&slot->hotplug_slot, acpiphp_slot->bus,
				 acpiphp_slot->device, name);
	if (retval == -EBUSY)
		goto error_slot;
	if (retval) {
		pr_err("pci_hp_register failed with error %d\n", retval);
		goto error_slot;
	}

	pr_info("Slot [%s] registered\n", slot_name(slot));

	return 0;
error_slot:
	kfree(slot);
error:
	return retval;
}