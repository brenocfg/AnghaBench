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
struct abx500_chargalg {int maintenance_chg; int /*<<< orphan*/  chargalg_psy; int /*<<< orphan*/  chargalg_wd_work; int /*<<< orphan*/  charge_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  abx500_chargalg_ac_en (struct abx500_chargalg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abx500_chargalg_stop_maintenance_timer (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_stop_safety_timer (struct abx500_chargalg*) ; 
 int /*<<< orphan*/  abx500_chargalg_usb_en (struct abx500_chargalg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abx500_chargalg_hold_charging(struct abx500_chargalg *di)
{
	abx500_chargalg_ac_en(di, false, 0, 0);
	abx500_chargalg_usb_en(di, false, 0, 0);
	abx500_chargalg_stop_safety_timer(di);
	abx500_chargalg_stop_maintenance_timer(di);
	di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
	di->maintenance_chg = false;
	cancel_delayed_work(&di->chargalg_wd_work);
	power_supply_changed(di->chargalg_psy);
}