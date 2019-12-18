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
struct slot {TYPE_1__* zdev; } ;
struct hotplug_slot {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZPCI_DEVFN ; 
 scalar_t__ ZPCI_FN_STATE_STANDBY ; 
 int /*<<< orphan*/  pci_bus_add_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_scan_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int slot_configure (struct slot*) ; 
 int /*<<< orphan*/  slot_deconfigure (struct slot*) ; 
 struct slot* to_slot (struct hotplug_slot*) ; 
 int zpci_enable_device (TYPE_1__*) ; 

__attribute__((used)) static int enable_slot(struct hotplug_slot *hotplug_slot)
{
	struct slot *slot = to_slot(hotplug_slot);
	int rc;

	if (slot->zdev->state != ZPCI_FN_STATE_STANDBY)
		return -EIO;

	rc = slot_configure(slot);
	if (rc)
		return rc;

	rc = zpci_enable_device(slot->zdev);
	if (rc)
		goto out_deconfigure;

	pci_scan_slot(slot->zdev->bus, ZPCI_DEVFN);
	pci_lock_rescan_remove();
	pci_bus_add_devices(slot->zdev->bus);
	pci_unlock_rescan_remove();

	return rc;

out_deconfigure:
	slot_deconfigure(slot);
	return rc;
}