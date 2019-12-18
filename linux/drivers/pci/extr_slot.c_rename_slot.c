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
struct pci_slot {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int kobject_rename (int /*<<< orphan*/ *,char*) ; 
 char* make_slot_name (char const*) ; 
 int /*<<< orphan*/  pci_slot_name (struct pci_slot*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int rename_slot(struct pci_slot *slot, const char *name)
{
	int result = 0;
	char *slot_name;

	if (strcmp(pci_slot_name(slot), name) == 0)
		return result;

	slot_name = make_slot_name(name);
	if (!slot_name)
		return -ENOMEM;

	result = kobject_rename(&slot->kobj, slot_name);
	kfree(slot_name);

	return result;
}