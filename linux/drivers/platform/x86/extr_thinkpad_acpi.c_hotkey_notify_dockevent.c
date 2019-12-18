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
typedef  int u32 ;

/* Variables and functions */
#define  TP_HKEY_EV_HOTPLUG_DOCK 130 
#define  TP_HKEY_EV_HOTPLUG_UNDOCK 129 
#define  TP_HKEY_EV_UNDOCK_ACK 128 
 int hotkey_autosleep_ack ; 
 int /*<<< orphan*/  hotkey_wakeup_hotunplug_complete_notify_change () ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static bool hotkey_notify_dockevent(const u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
{
	/* 0x4000-0x4FFF: dock-related events */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	switch (hkey) {
	case TP_HKEY_EV_UNDOCK_ACK:
		/* ACPI undock operation completed after wakeup */
		hotkey_autosleep_ack = 1;
		pr_info("undocked\n");
		hotkey_wakeup_hotunplug_complete_notify_change();
		return true;

	case TP_HKEY_EV_HOTPLUG_DOCK: /* docked to port replicator */
		pr_info("docked into hotplug port replicator\n");
		return true;
	case TP_HKEY_EV_HOTPLUG_UNDOCK: /* undocked from port replicator */
		pr_info("undocked from hotplug port replicator\n");
		return true;

	default:
		return false;
	}
}