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
struct watchdog_device {int dummy; } ;
struct da9055_wdt_data {struct da9055* da9055; } ;
struct da9055 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_CONTROL_E ; 
 int /*<<< orphan*/  DA9055_TWDMIN ; 
 int /*<<< orphan*/  DA9055_WATCHDOG_MASK ; 
 int da9055_reg_update (struct da9055*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 struct da9055_wdt_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int da9055_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct da9055_wdt_data *driver_data = watchdog_get_drvdata(wdt_dev);
	struct da9055 *da9055 = driver_data->da9055;

	/*
	 * We have a minimum time for watchdog window called TWDMIN. A write
	 * to the watchdog before this elapsed time will cause an error.
	 */
	mdelay(DA9055_TWDMIN);

	/* Reset the watchdog timer */
	return da9055_reg_update(da9055, DA9055_REG_CONTROL_E,
				 DA9055_WATCHDOG_MASK, 1);
}