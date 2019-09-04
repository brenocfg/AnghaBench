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
typedef  int u8 ;
struct watchdog_device {int dummy; } ;
struct sch56xx_watchdog_data {int watchdog_output_enable; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCH56XX_REG_WDOG_OUTPUT_ENABLE ; 
 int SCH56XX_WDOG_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int sch56xx_write_virtual_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sch56xx_watchdog_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_stop(struct watchdog_device *wddev)
{
	struct sch56xx_watchdog_data *data = watchdog_get_drvdata(wddev);
	int ret = 0;
	u8 val;

	val = data->watchdog_output_enable & ~SCH56XX_WDOG_OUTPUT_ENABLE;
	mutex_lock(data->io_lock);
	ret = sch56xx_write_virtual_reg(data->addr,
					SCH56XX_REG_WDOG_OUTPUT_ENABLE, val);
	mutex_unlock(data->io_lock);
	if (ret)
		return ret;

	data->watchdog_output_enable = val;
	return 0;
}