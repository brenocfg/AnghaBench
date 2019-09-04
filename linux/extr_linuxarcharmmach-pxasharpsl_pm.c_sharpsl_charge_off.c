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
struct TYPE_4__ {int /*<<< orphan*/  charge_mode; TYPE_1__* machinfo; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* charge ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHRG_OFF ; 
 int /*<<< orphan*/  SHARPSL_LED_OFF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_bat ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  sharpsl_pm_led (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sharpsl_charge_off(void)
{
	dev_dbg(sharpsl_pm.dev, "Turning Charger Off\n");

	sharpsl_pm.machinfo->charge(0);
	sharpsl_pm_led(SHARPSL_LED_OFF);
	sharpsl_pm.charge_mode = CHRG_OFF;

	schedule_delayed_work(&sharpsl_bat, 0);
}