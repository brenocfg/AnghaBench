#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int safety_timer_expired; scalar_t__ btemp_underover; scalar_t__ usb_wd_expired; scalar_t__ ac_wd_expired; scalar_t__ btemp_lowhigh; int /*<<< orphan*/  maintenance_timer_expired; scalar_t__ usbchargernotok; scalar_t__ mainextchnotok; scalar_t__ batt_ovv; scalar_t__ main_ovv; scalar_t__ vbus_ovv; scalar_t__ usb_thermal_prot; scalar_t__ main_thermal_prot; scalar_t__ batt_rem; int /*<<< orphan*/  usb_cv_active; int /*<<< orphan*/  ac_cv_active; int /*<<< orphan*/  vbus_collapsed; scalar_t__ batt_unknown; } ;
struct TYPE_11__ {int /*<<< orphan*/  percent; int /*<<< orphan*/  temp; int /*<<< orphan*/  inst_curr; int /*<<< orphan*/  avg_curr; int /*<<< orphan*/  volt; } ;
struct TYPE_10__ {int curr_step; } ;
struct TYPE_9__ {int conn_chg; int online_chg; scalar_t__ ac_chg_ok; scalar_t__ usb_chg_ok; int /*<<< orphan*/  usb_iset; int /*<<< orphan*/  usb_vset; int /*<<< orphan*/  ac_iset; int /*<<< orphan*/  ac_vset; int /*<<< orphan*/  usb_curr; int /*<<< orphan*/  ac_curr; int /*<<< orphan*/  charger_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  usb_suspended; int /*<<< orphan*/  ac_suspended; } ;
struct abx500_chargalg {int charge_state; int maintenance_chg; int /*<<< orphan*/  chargalg_work; int /*<<< orphan*/  chargalg_wq; TYPE_7__ events; int /*<<< orphan*/  chargalg_psy; void* charge_status; TYPE_6__* bm; TYPE_4__ batt_data; int /*<<< orphan*/  eoc_cnt; TYPE_3__ curr_status; TYPE_2__ chg_info; TYPE_1__ susp_status; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
struct TYPE_13__ {size_t batt_id; TYPE_5__* bat_type; int /*<<< orphan*/  no_maintenance; int /*<<< orphan*/  chg_unknown_bat; } ;
struct TYPE_12__ {int normal_cur_lvl; int maint_a_cur_lvl; int maint_b_cur_lvl; int low_high_cur_lvl; int /*<<< orphan*/  low_high_vol_lvl; int /*<<< orphan*/  maint_b_vol_lvl; int /*<<< orphan*/  maint_b_chg_timer_h; int /*<<< orphan*/  maint_a_vol_lvl; int /*<<< orphan*/  maint_a_chg_timer_h; int /*<<< orphan*/  recharge_cap; int /*<<< orphan*/  normal_vol_lvl; } ;

/* Variables and functions */
 int AC_CHG ; 
 int CHARGALG_CURR_STEP_HIGH ; 
 int CHARGALG_CURR_STEP_LOW ; 
 void* POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_DISCHARGING ; 
 void* POWER_SUPPLY_STATUS_FULL ; 
 void* POWER_SUPPLY_STATUS_NOT_CHARGING ; 
#define  STATE_BATT_REMOVED 155 
#define  STATE_BATT_REMOVED_INIT 154 
#define  STATE_CHG_NOT_OK 153 
#define  STATE_CHG_NOT_OK_INIT 152 
#define  STATE_HANDHELD 151 
#define  STATE_HANDHELD_INIT 150 
#define  STATE_HW_TEMP_PROTECT 149 
#define  STATE_HW_TEMP_PROTECT_INIT 148 
#define  STATE_MAINTENANCE_A 147 
#define  STATE_MAINTENANCE_A_INIT 146 
#define  STATE_MAINTENANCE_B 145 
#define  STATE_MAINTENANCE_B_INIT 144 
#define  STATE_NORMAL 143 
#define  STATE_NORMAL_INIT 142 
#define  STATE_OVV_PROTECT 141 
#define  STATE_OVV_PROTECT_INIT 140 
#define  STATE_SAFETY_TIMER_EXPIRED 139 
#define  STATE_SAFETY_TIMER_EXPIRED_INIT 138 
#define  STATE_SUSPENDED 137 
#define  STATE_SUSPENDED_INIT 136 
#define  STATE_TEMP_LOWHIGH 135 
#define  STATE_TEMP_LOWHIGH_INIT 134 
#define  STATE_TEMP_UNDEROVER 133 
#define  STATE_TEMP_UNDEROVER_INIT 132 
#define  STATE_WAIT_FOR_RECHARGE 131 
#define  STATE_WAIT_FOR_RECHARGE_INIT 130 
#define  STATE_WD_EXPIRED 129 
#define  STATE_WD_EXPIRED_INIT 128 
 int USB_CHG ; 
 int /*<<< orphan*/  abx500_chargalg_ac_en (struct abx500_chargalg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int abx500_chargalg_check_charger_connection (struct abx500_chargalg*) ; 
 int abx500_chargalg_check_charger_enable (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_check_charger_voltage (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_check_current_step_status (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_check_temp (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_end_of_charge (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_get_ext_psy_data ; 
 int /*<<< orphan*/  abx500_chargalg_hold_charging (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_start_charging (struct abx500_chargalg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  abx500_chargalg_start_maintenance_timer (struct abx500_chargalg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abx500_chargalg_start_safety_timer (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_state_to (struct abx500_chargalg*,int const) ; 
 int /*<<< orphan*/  abx500_chargalg_stop_charging (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_stop_maintenance_timer (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_stop_safety_timer (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_usb_en (struct abx500_chargalg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_for_each_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  handle_maxim_chg_curr (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  init_maxim_chg_curr (struct abx500_chargalg*) ; 
 scalar_t__ is_ab8500 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_class ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * states ; 

__attribute__((used)) static void abx500_chargalg_algorithm(struct abx500_chargalg *di)
{
	int charger_status;
	int ret;
	int curr_step_lvl;

	/* Collect data from all power_supply class devices */
	class_for_each_device(power_supply_class, NULL,
		di->chargalg_psy, abx500_chargalg_get_ext_psy_data);

	abx500_chargalg_end_of_charge(di);
	abx500_chargalg_check_temp(di);
	abx500_chargalg_check_charger_voltage(di);

	charger_status = abx500_chargalg_check_charger_connection(di);
	abx500_chargalg_check_current_step_status(di);

	if (is_ab8500(di->parent)) {
		ret = abx500_chargalg_check_charger_enable(di);
		if (ret < 0)
			dev_err(di->dev, "Checking charger is enabled error"
					": Returned Value %d\n", ret);
	}

	/*
	 * First check if we have a charger connected.
	 * Also we don't allow charging of unknown batteries if configured
	 * this way
	 */
	if (!charger_status ||
		(di->events.batt_unknown && !di->bm->chg_unknown_bat)) {
		if (di->charge_state != STATE_HANDHELD) {
			di->events.safety_timer_expired = false;
			abx500_chargalg_state_to(di, STATE_HANDHELD_INIT);
		}
	}

	/* If suspended, we should not continue checking the flags */
	else if (di->charge_state == STATE_SUSPENDED_INIT ||
		di->charge_state == STATE_SUSPENDED) {
		/* We don't do anything here, just don,t continue */
	}

	/* Safety timer expiration */
	else if (di->events.safety_timer_expired) {
		if (di->charge_state != STATE_SAFETY_TIMER_EXPIRED)
			abx500_chargalg_state_to(di,
				STATE_SAFETY_TIMER_EXPIRED_INIT);
	}
	/*
	 * Check if any interrupts has occured
	 * that will prevent us from charging
	 */

	/* Battery removed */
	else if (di->events.batt_rem) {
		if (di->charge_state != STATE_BATT_REMOVED)
			abx500_chargalg_state_to(di, STATE_BATT_REMOVED_INIT);
	}
	/* Main or USB charger not ok. */
	else if (di->events.mainextchnotok || di->events.usbchargernotok) {
		/*
		 * If vbus_collapsed is set, we have to lower the charger
		 * current, which is done in the normal state below
		 */
		if (di->charge_state != STATE_CHG_NOT_OK &&
				!di->events.vbus_collapsed)
			abx500_chargalg_state_to(di, STATE_CHG_NOT_OK_INIT);
	}
	/* VBUS, Main or VBAT OVV. */
	else if (di->events.vbus_ovv ||
			di->events.main_ovv ||
			di->events.batt_ovv ||
			!di->chg_info.usb_chg_ok ||
			!di->chg_info.ac_chg_ok) {
		if (di->charge_state != STATE_OVV_PROTECT)
			abx500_chargalg_state_to(di, STATE_OVV_PROTECT_INIT);
	}
	/* USB Thermal, stop charging */
	else if (di->events.main_thermal_prot ||
		di->events.usb_thermal_prot) {
		if (di->charge_state != STATE_HW_TEMP_PROTECT)
			abx500_chargalg_state_to(di,
				STATE_HW_TEMP_PROTECT_INIT);
	}
	/* Battery temp over/under */
	else if (di->events.btemp_underover) {
		if (di->charge_state != STATE_TEMP_UNDEROVER)
			abx500_chargalg_state_to(di,
				STATE_TEMP_UNDEROVER_INIT);
	}
	/* Watchdog expired */
	else if (di->events.ac_wd_expired ||
		di->events.usb_wd_expired) {
		if (di->charge_state != STATE_WD_EXPIRED)
			abx500_chargalg_state_to(di, STATE_WD_EXPIRED_INIT);
	}
	/* Battery temp high/low */
	else if (di->events.btemp_lowhigh) {
		if (di->charge_state != STATE_TEMP_LOWHIGH)
			abx500_chargalg_state_to(di, STATE_TEMP_LOWHIGH_INIT);
	}

	dev_dbg(di->dev,
		"[CHARGALG] Vb %d Ib_avg %d Ib_inst %d Tb %d Cap %d Maint %d "
		"State %s Active_chg %d Chg_status %d AC %d USB %d "
		"AC_online %d USB_online %d AC_CV %d USB_CV %d AC_I %d "
		"USB_I %d AC_Vset %d AC_Iset %d USB_Vset %d USB_Iset %d\n",
		di->batt_data.volt,
		di->batt_data.avg_curr,
		di->batt_data.inst_curr,
		di->batt_data.temp,
		di->batt_data.percent,
		di->maintenance_chg,
		states[di->charge_state],
		di->chg_info.charger_type,
		di->charge_status,
		di->chg_info.conn_chg & AC_CHG,
		di->chg_info.conn_chg & USB_CHG,
		di->chg_info.online_chg & AC_CHG,
		di->chg_info.online_chg & USB_CHG,
		di->events.ac_cv_active,
		di->events.usb_cv_active,
		di->chg_info.ac_curr,
		di->chg_info.usb_curr,
		di->chg_info.ac_vset,
		di->chg_info.ac_iset,
		di->chg_info.usb_vset,
		di->chg_info.usb_iset);

	switch (di->charge_state) {
	case STATE_HANDHELD_INIT:
		abx500_chargalg_stop_charging(di);
		di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;
		abx500_chargalg_state_to(di, STATE_HANDHELD);
		/* Intentional fallthrough */

	case STATE_HANDHELD:
		break;

	case STATE_SUSPENDED_INIT:
		if (di->susp_status.ac_suspended)
			abx500_chargalg_ac_en(di, false, 0, 0);
		if (di->susp_status.usb_suspended)
			abx500_chargalg_usb_en(di, false, 0, 0);
		abx500_chargalg_stop_safety_timer(di);
		abx500_chargalg_stop_maintenance_timer(di);
		di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		di->maintenance_chg = false;
		abx500_chargalg_state_to(di, STATE_SUSPENDED);
		power_supply_changed(di->chargalg_psy);
		/* Intentional fallthrough */

	case STATE_SUSPENDED:
		/* CHARGING is suspended */
		break;

	case STATE_BATT_REMOVED_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_BATT_REMOVED);
		/* Intentional fallthrough */

	case STATE_BATT_REMOVED:
		if (!di->events.batt_rem)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_HW_TEMP_PROTECT_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_HW_TEMP_PROTECT);
		/* Intentional fallthrough */

	case STATE_HW_TEMP_PROTECT:
		if (!di->events.main_thermal_prot &&
				!di->events.usb_thermal_prot)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_OVV_PROTECT_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_OVV_PROTECT);
		/* Intentional fallthrough */

	case STATE_OVV_PROTECT:
		if (!di->events.vbus_ovv &&
				!di->events.main_ovv &&
				!di->events.batt_ovv &&
				di->chg_info.usb_chg_ok &&
				di->chg_info.ac_chg_ok)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_CHG_NOT_OK_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_CHG_NOT_OK);
		/* Intentional fallthrough */

	case STATE_CHG_NOT_OK:
		if (!di->events.mainextchnotok &&
				!di->events.usbchargernotok)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_SAFETY_TIMER_EXPIRED_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_SAFETY_TIMER_EXPIRED);
		/* Intentional fallthrough */

	case STATE_SAFETY_TIMER_EXPIRED:
		/* We exit this state when charger is removed */
		break;

	case STATE_NORMAL_INIT:
		if (di->curr_status.curr_step == CHARGALG_CURR_STEP_LOW)
			abx500_chargalg_stop_charging(di);
		else {
			curr_step_lvl = di->bm->bat_type[
				di->bm->batt_id].normal_cur_lvl
				* di->curr_status.curr_step
				/ CHARGALG_CURR_STEP_HIGH;
			abx500_chargalg_start_charging(di,
				di->bm->bat_type[di->bm->batt_id]
				.normal_vol_lvl, curr_step_lvl);
		}

		abx500_chargalg_state_to(di, STATE_NORMAL);
		abx500_chargalg_start_safety_timer(di);
		abx500_chargalg_stop_maintenance_timer(di);
		init_maxim_chg_curr(di);
		di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
		di->eoc_cnt = 0;
		di->maintenance_chg = false;
		power_supply_changed(di->chargalg_psy);

		break;

	case STATE_NORMAL:
		handle_maxim_chg_curr(di);
		if (di->charge_status == POWER_SUPPLY_STATUS_FULL &&
			di->maintenance_chg) {
			if (di->bm->no_maintenance)
				abx500_chargalg_state_to(di,
					STATE_WAIT_FOR_RECHARGE_INIT);
			else
				abx500_chargalg_state_to(di,
					STATE_MAINTENANCE_A_INIT);
		}
		break;

	/* This state will be used when the maintenance state is disabled */
	case STATE_WAIT_FOR_RECHARGE_INIT:
		abx500_chargalg_hold_charging(di);
		abx500_chargalg_state_to(di, STATE_WAIT_FOR_RECHARGE);
		/* Intentional fallthrough */

	case STATE_WAIT_FOR_RECHARGE:
		if (di->batt_data.percent <=
		    di->bm->bat_type[di->bm->batt_id].
		    recharge_cap)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_MAINTENANCE_A_INIT:
		abx500_chargalg_stop_safety_timer(di);
		abx500_chargalg_start_maintenance_timer(di,
			di->bm->bat_type[
				di->bm->batt_id].maint_a_chg_timer_h);
		abx500_chargalg_start_charging(di,
			di->bm->bat_type[
				di->bm->batt_id].maint_a_vol_lvl,
			di->bm->bat_type[
				di->bm->batt_id].maint_a_cur_lvl);
		abx500_chargalg_state_to(di, STATE_MAINTENANCE_A);
		power_supply_changed(di->chargalg_psy);
		/* Intentional fallthrough*/

	case STATE_MAINTENANCE_A:
		if (di->events.maintenance_timer_expired) {
			abx500_chargalg_stop_maintenance_timer(di);
			abx500_chargalg_state_to(di, STATE_MAINTENANCE_B_INIT);
		}
		break;

	case STATE_MAINTENANCE_B_INIT:
		abx500_chargalg_start_maintenance_timer(di,
			di->bm->bat_type[
				di->bm->batt_id].maint_b_chg_timer_h);
		abx500_chargalg_start_charging(di,
			di->bm->bat_type[
				di->bm->batt_id].maint_b_vol_lvl,
			di->bm->bat_type[
				di->bm->batt_id].maint_b_cur_lvl);
		abx500_chargalg_state_to(di, STATE_MAINTENANCE_B);
		power_supply_changed(di->chargalg_psy);
		/* Intentional fallthrough*/

	case STATE_MAINTENANCE_B:
		if (di->events.maintenance_timer_expired) {
			abx500_chargalg_stop_maintenance_timer(di);
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		}
		break;

	case STATE_TEMP_LOWHIGH_INIT:
		abx500_chargalg_start_charging(di,
			di->bm->bat_type[
				di->bm->batt_id].low_high_vol_lvl,
			di->bm->bat_type[
				di->bm->batt_id].low_high_cur_lvl);
		abx500_chargalg_stop_maintenance_timer(di);
		di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
		abx500_chargalg_state_to(di, STATE_TEMP_LOWHIGH);
		power_supply_changed(di->chargalg_psy);
		/* Intentional fallthrough */

	case STATE_TEMP_LOWHIGH:
		if (!di->events.btemp_lowhigh)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_WD_EXPIRED_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_WD_EXPIRED);
		/* Intentional fallthrough */

	case STATE_WD_EXPIRED:
		if (!di->events.ac_wd_expired &&
				!di->events.usb_wd_expired)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;

	case STATE_TEMP_UNDEROVER_INIT:
		abx500_chargalg_stop_charging(di);
		abx500_chargalg_state_to(di, STATE_TEMP_UNDEROVER);
		/* Intentional fallthrough */

	case STATE_TEMP_UNDEROVER:
		if (!di->events.btemp_underover)
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		break;
	}

	/* Start charging directly if the new state is a charge state */
	if (di->charge_state == STATE_NORMAL_INIT ||
			di->charge_state == STATE_MAINTENANCE_A_INIT ||
			di->charge_state == STATE_MAINTENANCE_B_INIT)
		queue_work(di->chargalg_wq, &di->chargalg_work);
}