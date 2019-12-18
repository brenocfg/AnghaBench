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
struct eeepc_laptop {scalar_t__ wimax_rfkill; scalar_t__ wwan3g_rfkill; scalar_t__ bluetooth_rfkill; scalar_t__ wlan_rfkill; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_3G ; 
 int /*<<< orphan*/  CM_ASL_BLUETOOTH ; 
 int /*<<< orphan*/  CM_ASL_WIMAX ; 
 int /*<<< orphan*/  EEEPC_RFKILL_NODE_1 ; 
 int /*<<< orphan*/  EEEPC_RFKILL_NODE_2 ; 
 int /*<<< orphan*/  EEEPC_RFKILL_NODE_3 ; 
 struct eeepc_laptop* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  eeepc_rfkill_hotplug_update (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 
 int get_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (scalar_t__,int) ; 

__attribute__((used)) static int eeepc_hotk_restore(struct device *device)
{
	struct eeepc_laptop *eeepc = dev_get_drvdata(device);

	/* Refresh both wlan rfkill state and pci hotplug */
	if (eeepc->wlan_rfkill) {
		eeepc_rfkill_hotplug_update(eeepc, EEEPC_RFKILL_NODE_1);
		eeepc_rfkill_hotplug_update(eeepc, EEEPC_RFKILL_NODE_2);
		eeepc_rfkill_hotplug_update(eeepc, EEEPC_RFKILL_NODE_3);
	}

	if (eeepc->bluetooth_rfkill)
		rfkill_set_sw_state(eeepc->bluetooth_rfkill,
				    get_acpi(eeepc, CM_ASL_BLUETOOTH) != 1);
	if (eeepc->wwan3g_rfkill)
		rfkill_set_sw_state(eeepc->wwan3g_rfkill,
				    get_acpi(eeepc, CM_ASL_3G) != 1);
	if (eeepc->wimax_rfkill)
		rfkill_set_sw_state(eeepc->wimax_rfkill,
				    get_acpi(eeepc, CM_ASL_WIMAX) != 1);

	return 0;
}