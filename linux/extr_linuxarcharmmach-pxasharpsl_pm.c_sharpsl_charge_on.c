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
struct TYPE_2__ {int /*<<< orphan*/  charge_mode; scalar_t__ full_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHRG_ON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_bat ; 
 TYPE_1__ sharpsl_pm ; 
 int /*<<< orphan*/  toggle_charger ; 

__attribute__((used)) static void sharpsl_charge_on(void)
{
	dev_dbg(sharpsl_pm.dev, "Turning Charger On\n");

	sharpsl_pm.full_count = 0;
	sharpsl_pm.charge_mode = CHRG_ON;
	schedule_delayed_work(&toggle_charger, msecs_to_jiffies(250));
	schedule_delayed_work(&sharpsl_bat, msecs_to_jiffies(500));
}