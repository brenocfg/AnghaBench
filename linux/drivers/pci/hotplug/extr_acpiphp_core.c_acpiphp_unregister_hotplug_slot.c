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
struct slot {int /*<<< orphan*/  hotplug_slot; } ;
struct acpiphp_slot {struct slot* slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct slot*) ; 
 int /*<<< orphan*/  pci_hp_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

void acpiphp_unregister_hotplug_slot(struct acpiphp_slot *acpiphp_slot)
{
	struct slot *slot = acpiphp_slot->slot;

	pr_info("Slot [%s] unregistered\n", slot_name(slot));

	pci_hp_deregister(&slot->hotplug_slot);
	kfree(slot);
}