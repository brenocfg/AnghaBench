#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * rfkill; } ;
struct TYPE_14__ {int /*<<< orphan*/ * rfkill; } ;
struct TYPE_13__ {int /*<<< orphan*/ * rfkill; } ;
struct TYPE_12__ {int /*<<< orphan*/ * rfkill; } ;
struct TYPE_11__ {int /*<<< orphan*/ * rfkill; } ;
struct TYPE_16__ {scalar_t__ ops; } ;
struct TYPE_10__ {int /*<<< orphan*/ * rfkill; } ;
struct asus_wmi {TYPE_7__ uwb; TYPE_6__ gps; TYPE_5__ wwan3g; TYPE_4__ wimax; TYPE_3__ bluetooth; scalar_t__ hotplug_workqueue; TYPE_8__ hotplug_slot; TYPE_2__ wlan; TYPE_1__* driver; } ;
struct TYPE_9__ {scalar_t__ wlan_ctrl_by_user; } ;

/* Variables and functions */
 scalar_t__ ashs_present () ; 
 int /*<<< orphan*/  asus_rfkill_hotplug (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_unregister_rfkill_notifier (struct asus_wmi*,char*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  pci_hp_deregister (TYPE_8__*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asus_wmi_rfkill_exit(struct asus_wmi *asus)
{
	if (asus->driver->wlan_ctrl_by_user && ashs_present())
		return;

	asus_unregister_rfkill_notifier(asus, "\\_SB.PCI0.P0P5");
	asus_unregister_rfkill_notifier(asus, "\\_SB.PCI0.P0P6");
	asus_unregister_rfkill_notifier(asus, "\\_SB.PCI0.P0P7");
	if (asus->wlan.rfkill) {
		rfkill_unregister(asus->wlan.rfkill);
		rfkill_destroy(asus->wlan.rfkill);
		asus->wlan.rfkill = NULL;
	}
	/*
	 * Refresh pci hotplug in case the rfkill state was changed after
	 * asus_unregister_rfkill_notifier()
	 */
	asus_rfkill_hotplug(asus);
	if (asus->hotplug_slot.ops)
		pci_hp_deregister(&asus->hotplug_slot);
	if (asus->hotplug_workqueue)
		destroy_workqueue(asus->hotplug_workqueue);

	if (asus->bluetooth.rfkill) {
		rfkill_unregister(asus->bluetooth.rfkill);
		rfkill_destroy(asus->bluetooth.rfkill);
		asus->bluetooth.rfkill = NULL;
	}
	if (asus->wimax.rfkill) {
		rfkill_unregister(asus->wimax.rfkill);
		rfkill_destroy(asus->wimax.rfkill);
		asus->wimax.rfkill = NULL;
	}
	if (asus->wwan3g.rfkill) {
		rfkill_unregister(asus->wwan3g.rfkill);
		rfkill_destroy(asus->wwan3g.rfkill);
		asus->wwan3g.rfkill = NULL;
	}
	if (asus->gps.rfkill) {
		rfkill_unregister(asus->gps.rfkill);
		rfkill_destroy(asus->gps.rfkill);
		asus->gps.rfkill = NULL;
	}
	if (asus->uwb.rfkill) {
		rfkill_unregister(asus->uwb.rfkill);
		rfkill_destroy(asus->uwb.rfkill);
		asus->uwb.rfkill = NULL;
	}
}