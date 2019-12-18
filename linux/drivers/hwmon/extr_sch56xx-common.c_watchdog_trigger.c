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
struct sch56xx_watchdog_data {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  watchdog_preset; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCH56XX_REG_WDOG_PRESET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int sch56xx_write_virtual_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sch56xx_watchdog_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_trigger(struct watchdog_device *wddev)
{
	struct sch56xx_watchdog_data *data = watchdog_get_drvdata(wddev);
	int ret;

	/* Reset the watchdog countdown counter */
	mutex_lock(data->io_lock);
	ret = sch56xx_write_virtual_reg(data->addr, SCH56XX_REG_WDOG_PRESET,
					data->watchdog_preset);
	mutex_unlock(data->io_lock);

	return ret;
}