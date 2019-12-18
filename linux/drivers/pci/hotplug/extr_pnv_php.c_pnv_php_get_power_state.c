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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct pnv_php_slot {int /*<<< orphan*/  pdev; int /*<<< orphan*/  id; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_PCI_SLOT_POWER_ON ; 
 int /*<<< orphan*/  pci_warn (int /*<<< orphan*/ ,char*,int) ; 
 int pnv_pci_get_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int pnv_php_get_power_state(struct hotplug_slot *slot, u8 *state)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	uint8_t power_state = OPAL_PCI_SLOT_POWER_ON;
	int ret;

	/*
	 * Retrieve power status from firmware. If we fail
	 * getting that, the power status fails back to
	 * be on.
	 */
	ret = pnv_pci_get_power_state(php_slot->id, &power_state);
	if (ret) {
		pci_warn(php_slot->pdev, "Error %d getting power status\n",
			 ret);
	} else {
		*state = power_state;
	}

	return 0;
}