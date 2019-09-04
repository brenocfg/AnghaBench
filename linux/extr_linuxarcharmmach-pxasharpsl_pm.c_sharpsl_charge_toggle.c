#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  charge_start_time; TYPE_1__* machinfo; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* charge ) (int) ;int /*<<< orphan*/  (* read_devdata ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SHARPSL_CHARGE_WAIT_TIME ; 
 int /*<<< orphan*/  SHARPSL_LED_ON ; 
 int /*<<< orphan*/  SHARPSL_STATUS_ACIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 scalar_t__ sharpsl_ac_check () ; 
 int /*<<< orphan*/  sharpsl_charge_error () ; 
 int /*<<< orphan*/  sharpsl_charge_off () ; 
 scalar_t__ sharpsl_check_battery_temp () ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  sharpsl_pm_led (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int) ; 

__attribute__((used)) static void sharpsl_charge_toggle(struct work_struct *private_)
{
	dev_dbg(sharpsl_pm.dev, "Toggling Charger at time: %lx\n", jiffies);

	if (!sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_ACIN)) {
		sharpsl_charge_off();
		return;
	} else if ((sharpsl_check_battery_temp() < 0) || (sharpsl_ac_check() < 0)) {
		sharpsl_charge_error();
		return;
	}

	sharpsl_pm_led(SHARPSL_LED_ON);
	sharpsl_pm.machinfo->charge(0);
	mdelay(SHARPSL_CHARGE_WAIT_TIME);
	sharpsl_pm.machinfo->charge(1);

	sharpsl_pm.charge_start_time = jiffies;
}