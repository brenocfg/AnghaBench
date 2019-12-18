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
struct pnv_php_slot {scalar_t__ state; int /*<<< orphan*/  dn; int /*<<< orphan*/  bus; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_PCI_SLOT_POWER_OFF ; 
 scalar_t__ PNV_PHP_STATE_POPULATED ; 
 scalar_t__ PNV_PHP_STATE_REGISTERED ; 
 int /*<<< orphan*/  pci_hp_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int pnv_php_set_slot_power_state (struct hotplug_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_php_unregister (int /*<<< orphan*/ ) ; 
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int pnv_php_disable_slot(struct hotplug_slot *slot)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	int ret;

	if (php_slot->state != PNV_PHP_STATE_POPULATED)
		return 0;

	/* Remove all devices behind the slot */
	pci_lock_rescan_remove();
	pci_hp_remove_devices(php_slot->bus);
	pci_unlock_rescan_remove();

	/* Detach the child hotpluggable slots */
	pnv_php_unregister(php_slot->dn);

	/* Notify firmware and remove device nodes */
	ret = pnv_php_set_slot_power_state(slot, OPAL_PCI_SLOT_POWER_OFF);

	php_slot->state = PNV_PHP_STATE_REGISTERED;
	return ret;
}