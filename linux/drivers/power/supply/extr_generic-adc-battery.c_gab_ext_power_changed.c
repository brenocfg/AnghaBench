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
struct power_supply {int dummy; } ;
struct gab {int /*<<< orphan*/  bat_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gab* to_generic_bat (struct power_supply*) ; 

__attribute__((used)) static void gab_ext_power_changed(struct power_supply *psy)
{
	struct gab *adc_bat = to_generic_bat(psy);

	schedule_delayed_work(&adc_bat->bat_work, msecs_to_jiffies(0));
}