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
struct TYPE_2__ {scalar_t__ ops; } ;
struct eeepc_laptop {int /*<<< orphan*/ * wimax_rfkill; int /*<<< orphan*/ * wwan3g_rfkill; int /*<<< orphan*/ * bluetooth_rfkill; TYPE_1__ hotplug_slot; int /*<<< orphan*/ * wlan_rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEEPC_RFKILL_NODE_1 ; 
 int /*<<< orphan*/  EEEPC_RFKILL_NODE_2 ; 
 int /*<<< orphan*/  EEEPC_RFKILL_NODE_3 ; 
 int /*<<< orphan*/  eeepc_unregister_rfkill_notifier (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_hp_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeepc_rfkill_exit(struct eeepc_laptop *eeepc)
{
	eeepc_unregister_rfkill_notifier(eeepc, EEEPC_RFKILL_NODE_1);
	eeepc_unregister_rfkill_notifier(eeepc, EEEPC_RFKILL_NODE_2);
	eeepc_unregister_rfkill_notifier(eeepc, EEEPC_RFKILL_NODE_3);
	if (eeepc->wlan_rfkill) {
		rfkill_unregister(eeepc->wlan_rfkill);
		rfkill_destroy(eeepc->wlan_rfkill);
		eeepc->wlan_rfkill = NULL;
	}

	if (eeepc->hotplug_slot.ops)
		pci_hp_deregister(&eeepc->hotplug_slot);

	if (eeepc->bluetooth_rfkill) {
		rfkill_unregister(eeepc->bluetooth_rfkill);
		rfkill_destroy(eeepc->bluetooth_rfkill);
		eeepc->bluetooth_rfkill = NULL;
	}
	if (eeepc->wwan3g_rfkill) {
		rfkill_unregister(eeepc->wwan3g_rfkill);
		rfkill_destroy(eeepc->wwan3g_rfkill);
		eeepc->wwan3g_rfkill = NULL;
	}
	if (eeepc->wimax_rfkill) {
		rfkill_unregister(eeepc->wimax_rfkill);
		rfkill_destroy(eeepc->wimax_rfkill);
		eeepc->wimax_rfkill = NULL;
	}
}