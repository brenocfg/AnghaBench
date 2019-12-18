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
struct TYPE_2__ {int /*<<< orphan*/  wait_for_charger; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_work ; 
 int /*<<< orphan*/  update_charger () ; 

__attribute__((used)) static void psy_changed(void)
{
	update_charger();

	/*
	 * Okay, charger set. Now wait a bit before notifying supplicants,
	 * charge power should stabilize.
	 */
	cancel_delayed_work(&supply_work);
	schedule_delayed_work(&supply_work,
			      msecs_to_jiffies(pdata->wait_for_charger));
}