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
struct twl4030_madc_battery {int /*<<< orphan*/  channel_temp; int /*<<< orphan*/  channel_ichg; int /*<<< orphan*/  channel_vbat; int /*<<< orphan*/  psy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ ) ; 
 struct twl4030_madc_battery* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_madc_battery_remove(struct platform_device *pdev)
{
	struct twl4030_madc_battery *bat = platform_get_drvdata(pdev);

	power_supply_unregister(bat->psy);

	iio_channel_release(bat->channel_vbat);
	iio_channel_release(bat->channel_ichg);
	iio_channel_release(bat->channel_temp);

	return 0;
}