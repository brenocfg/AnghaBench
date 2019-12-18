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
struct zpci_dev {int fid; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct slot {int /*<<< orphan*/  slot_list; TYPE_1__ hotplug_slot; struct zpci_dev* zdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  ZPCI_DEVFN ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pci_hp_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  s390_hotplug_slot_list ; 
 int /*<<< orphan*/  s390_hotplug_slot_ops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int zpci_init_slot(struct zpci_dev *zdev)
{
	char name[SLOT_NAME_SIZE];
	struct slot *slot;
	int rc;

	if (!zdev)
		return 0;

	slot = kzalloc(sizeof(*slot), GFP_KERNEL);
	if (!slot)
		goto error;

	slot->zdev = zdev;
	slot->hotplug_slot.ops = &s390_hotplug_slot_ops;

	snprintf(name, SLOT_NAME_SIZE, "%08x", zdev->fid);
	rc = pci_hp_register(&slot->hotplug_slot, zdev->bus,
			     ZPCI_DEVFN, name);
	if (rc)
		goto error_reg;

	list_add(&slot->slot_list, &s390_hotplug_slot_list);
	return 0;

error_reg:
	kfree(slot);
error:
	return -ENOMEM;
}