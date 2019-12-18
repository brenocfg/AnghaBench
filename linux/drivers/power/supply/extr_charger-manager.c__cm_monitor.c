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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct charger_manager {int emergency_stop; TYPE_1__ fullbatt_vchk_work; int /*<<< orphan*/  dev; scalar_t__ charger_enabled; } ;

/* Variables and functions */
 size_t CM_EVENT_BATT_FULL ; 
 scalar_t__ check_charging_duration (struct charger_manager*) ; 
 int cm_check_thermal_status (struct charger_manager*) ; 
 char** default_event_names ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fullbatt_vchk (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ext_pwr_online (struct charger_manager*) ; 
 scalar_t__ is_full_charged (struct charger_manager*) ; 
 int /*<<< orphan*/  try_charger_enable (struct charger_manager*,int) ; 
 int /*<<< orphan*/  uevent_notify (struct charger_manager*,char*) ; 

__attribute__((used)) static bool _cm_monitor(struct charger_manager *cm)
{
	int temp_alrt;

	temp_alrt = cm_check_thermal_status(cm);

	/* It has been stopped already */
	if (temp_alrt && cm->emergency_stop)
		return false;

	/*
	 * Check temperature whether overheat or cold.
	 * If temperature is out of range normal state, stop charging.
	 */
	if (temp_alrt) {
		cm->emergency_stop = temp_alrt;
		if (!try_charger_enable(cm, false))
			uevent_notify(cm, default_event_names[temp_alrt]);

	/*
	 * Check whole charging duration and discharging duration
	 * after full-batt.
	 */
	} else if (!cm->emergency_stop && check_charging_duration(cm)) {
		dev_dbg(cm->dev,
			"Charging/Discharging duration is out of range\n");
	/*
	 * Check dropped voltage of battery. If battery voltage is more
	 * dropped than fullbatt_vchkdrop_uV after fully charged state,
	 * charger-manager have to recharge battery.
	 */
	} else if (!cm->emergency_stop && is_ext_pwr_online(cm) &&
			!cm->charger_enabled) {
		fullbatt_vchk(&cm->fullbatt_vchk_work.work);

	/*
	 * Check whether fully charged state to protect overcharge
	 * if charger-manager is charging for battery.
	 */
	} else if (!cm->emergency_stop && is_full_charged(cm) &&
			cm->charger_enabled) {
		dev_info(cm->dev, "EVENT_HANDLE: Battery Fully Charged\n");
		uevent_notify(cm, default_event_names[CM_EVENT_BATT_FULL]);

		try_charger_enable(cm, false);

		fullbatt_vchk(&cm->fullbatt_vchk_work.work);
	} else {
		cm->emergency_stop = 0;
		if (is_ext_pwr_online(cm)) {
			if (!try_charger_enable(cm, true))
				uevent_notify(cm, "CHARGING");
		}
	}

	return true;
}