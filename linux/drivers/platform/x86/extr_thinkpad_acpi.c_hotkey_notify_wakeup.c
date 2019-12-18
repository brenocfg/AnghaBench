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
 scalar_t__ TP_ACPI_WAKEUP_BAYEJ ; 
 scalar_t__ TP_ACPI_WAKEUP_NONE ; 
 scalar_t__ TP_ACPI_WAKEUP_UNDOCK ; 
#define  TP_HKEY_EV_WKUP_S3_BATLOW 133 
#define  TP_HKEY_EV_WKUP_S3_BAYEJ 132 
#define  TP_HKEY_EV_WKUP_S3_UNDOCK 131 
#define  TP_HKEY_EV_WKUP_S4_BATLOW 130 
#define  TP_HKEY_EV_WKUP_S4_BAYEJ 129 
#define  TP_HKEY_EV_WKUP_S4_UNDOCK 128 
 scalar_t__ hotkey_wakeup_reason ; 
 int /*<<< orphan*/  hotkey_wakeup_reason_notify_change () ; 
 int /*<<< orphan*/  pr_alert (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static bool hotkey_notify_wakeup(const u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
{
	/* 0x2000-0x2FFF: Wakeup reason */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	switch (hkey) {
	case TP_HKEY_EV_WKUP_S3_UNDOCK: /* suspend, undock */
	case TP_HKEY_EV_WKUP_S4_UNDOCK: /* hibernation, undock */
		hotkey_wakeup_reason = TP_ACPI_WAKEUP_UNDOCK;
		*ignore_acpi_ev = true;
		break;

	case TP_HKEY_EV_WKUP_S3_BAYEJ: /* suspend, bay eject */
	case TP_HKEY_EV_WKUP_S4_BAYEJ: /* hibernation, bay eject */
		hotkey_wakeup_reason = TP_ACPI_WAKEUP_BAYEJ;
		*ignore_acpi_ev = true;
		break;

	case TP_HKEY_EV_WKUP_S3_BATLOW: /* Battery on critical low level/S3 */
	case TP_HKEY_EV_WKUP_S4_BATLOW: /* Battery on critical low level/S4 */
		pr_alert("EMERGENCY WAKEUP: battery almost empty\n");
		/* how to auto-heal: */
		/* 2313: woke up from S3, go to S4/S5 */
		/* 2413: woke up from S4, go to S5 */
		break;

	default:
		return false;
	}

	if (hotkey_wakeup_reason != TP_ACPI_WAKEUP_NONE) {
		pr_info("woke up due to a hot-unplug request...\n");
		hotkey_wakeup_reason_notify_change();
	}
	return true;
}