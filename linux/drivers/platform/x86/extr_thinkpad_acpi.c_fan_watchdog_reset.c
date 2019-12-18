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

/* Variables and functions */
 scalar_t__ TPACPI_FAN_WR_NONE ; 
 scalar_t__ TPACPI_LIFE_EXITING ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ fan_control_access_mode ; 
 int fan_watchdog_maxinterval ; 
 int /*<<< orphan*/  fan_watchdog_task ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ tpacpi_lifecycle ; 
 int /*<<< orphan*/  tpacpi_wq ; 

__attribute__((used)) static void fan_watchdog_reset(void)
{
	if (fan_control_access_mode == TPACPI_FAN_WR_NONE)
		return;

	if (fan_watchdog_maxinterval > 0 &&
	    tpacpi_lifecycle != TPACPI_LIFE_EXITING)
		mod_delayed_work(tpacpi_wq, &fan_watchdog_task,
			msecs_to_jiffies(fan_watchdog_maxinterval * 1000));
	else
		cancel_delayed_work(&fan_watchdog_task);
}