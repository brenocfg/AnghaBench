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
struct pci_dev {int dummy; } ;
struct hotplug_slot {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZPCI_DEVFN ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device_locked (struct pci_dev*) ; 
 int slot_deconfigure (struct slot*) ; 
 struct slot* to_slot (struct hotplug_slot*) ; 
 int zpci_disable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  zpci_fn_configured (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disable_slot(struct hotplug_slot *hotplug_slot)
{
	struct slot *slot = to_slot(hotplug_slot);
	struct pci_dev *pdev;
	int rc;

	if (!zpci_fn_configured(slot->zdev->state))
		return -EIO;

	pdev = pci_get_slot(slot->zdev->bus, ZPCI_DEVFN);
	if (pdev) {
		pci_stop_and_remove_bus_device_locked(pdev);
		pci_dev_put(pdev);
	}

	rc = zpci_disable_device(slot->zdev);
	if (rc)
		return rc;

	return slot_deconfigure(slot);
}