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
#define  TP_HKEY_EV_AC_CHANGED 141 
#define  TP_HKEY_EV_ALARM_BAT_HOT 140 
#define  TP_HKEY_EV_ALARM_BAT_XHOT 139 
#define  TP_HKEY_EV_ALARM_SENSOR_HOT 138 
#define  TP_HKEY_EV_ALARM_SENSOR_XHOT 137 
#define  TP_HKEY_EV_KEY_FN 136 
#define  TP_HKEY_EV_KEY_FN_ESC 135 
#define  TP_HKEY_EV_KEY_NUMLOCK 134 
#define  TP_HKEY_EV_PALM_DETECTED 133 
#define  TP_HKEY_EV_PALM_UNDETECTED 132 
#define  TP_HKEY_EV_TABLET_CHANGED 131 
#define  TP_HKEY_EV_THM_CSM_COMPLETED 130 
#define  TP_HKEY_EV_THM_TABLE_CHANGED 129 
#define  TP_HKEY_EV_THM_TRANSFM_CHANGED 128 
 int /*<<< orphan*/  hotkey_tablet_mode_notify_change () ; 
 int /*<<< orphan*/  pr_alert (char*) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  thermal_dump_all_sensors () ; 
 int /*<<< orphan*/  tpacpi_input_send_tabletsw () ; 

__attribute__((used)) static bool hotkey_notify_6xxx(const u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
{
	/* 0x6000-0x6FFF: thermal alarms/notices and keyboard events */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	switch (hkey) {
	case TP_HKEY_EV_THM_TABLE_CHANGED:
		pr_debug("EC reports: Thermal Table has changed\n");
		/* recommended action: do nothing, we don't have
		 * Lenovo ATM information */
		return true;
	case TP_HKEY_EV_THM_CSM_COMPLETED:
		pr_debug("EC reports: Thermal Control Command set completed (DYTC)\n");
		/* recommended action: do nothing, we don't have
		 * Lenovo ATM information */
		return true;
	case TP_HKEY_EV_THM_TRANSFM_CHANGED:
		pr_debug("EC reports: Thermal Transformation changed (GMTS)\n");
		/* recommended action: do nothing, we don't have
		 * Lenovo ATM information */
		return true;
	case TP_HKEY_EV_ALARM_BAT_HOT:
		pr_crit("THERMAL ALARM: battery is too hot!\n");
		/* recommended action: warn user through gui */
		break;
	case TP_HKEY_EV_ALARM_BAT_XHOT:
		pr_alert("THERMAL EMERGENCY: battery is extremely hot!\n");
		/* recommended action: immediate sleep/hibernate */
		break;
	case TP_HKEY_EV_ALARM_SENSOR_HOT:
		pr_crit("THERMAL ALARM: a sensor reports something is too hot!\n");
		/* recommended action: warn user through gui, that */
		/* some internal component is too hot */
		break;
	case TP_HKEY_EV_ALARM_SENSOR_XHOT:
		pr_alert("THERMAL EMERGENCY: a sensor reports something is extremely hot!\n");
		/* recommended action: immediate sleep/hibernate */
		break;
	case TP_HKEY_EV_AC_CHANGED:
		/* X120e, X121e, X220, X220i, X220t, X230, T420, T420s, W520:
		 * AC status changed; can be triggered by plugging or
		 * unplugging AC adapter, docking or undocking. */

		/* fallthrough */

	case TP_HKEY_EV_KEY_NUMLOCK:
	case TP_HKEY_EV_KEY_FN:
	case TP_HKEY_EV_KEY_FN_ESC:
		/* key press events, we just ignore them as long as the EC
		 * is still reporting them in the normal keyboard stream */
		*send_acpi_ev = false;
		*ignore_acpi_ev = true;
		return true;

	case TP_HKEY_EV_TABLET_CHANGED:
		tpacpi_input_send_tabletsw();
		hotkey_tablet_mode_notify_change();
		*send_acpi_ev = false;
		return true;

	case TP_HKEY_EV_PALM_DETECTED:
	case TP_HKEY_EV_PALM_UNDETECTED:
		/* palm detected hovering the keyboard, forward to user-space
		 * via netlink for consumption */
		return true;

	default:
		/* report simply as unknown, no sensor dump */
		return false;
	}

	thermal_dump_all_sensors();
	return true;
}