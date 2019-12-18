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
struct menf21bmc_wdt {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC_CMD_WD_TRIG ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct menf21bmc_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int menf21bmc_wdt_ping(struct watchdog_device *wdt)
{
	struct menf21bmc_wdt *drv_data = watchdog_get_drvdata(wdt);

	return i2c_smbus_write_byte(drv_data->i2c_client, BMC_CMD_WD_TRIG);
}