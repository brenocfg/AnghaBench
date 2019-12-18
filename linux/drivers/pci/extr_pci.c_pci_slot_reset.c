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
struct pci_slot {int /*<<< orphan*/  hotplug; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pci_reset_hotplug_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_slot_lock (struct pci_slot*) ; 
 int /*<<< orphan*/  pci_slot_resetable (struct pci_slot*) ; 
 int /*<<< orphan*/  pci_slot_unlock (struct pci_slot*) ; 

__attribute__((used)) static int pci_slot_reset(struct pci_slot *slot, int probe)
{
	int rc;

	if (!slot || !pci_slot_resetable(slot))
		return -ENOTTY;

	if (!probe)
		pci_slot_lock(slot);

	might_sleep();

	rc = pci_reset_hotplug_slot(slot->hotplug, probe);

	if (!probe)
		pci_slot_unlock(slot);

	return rc;
}