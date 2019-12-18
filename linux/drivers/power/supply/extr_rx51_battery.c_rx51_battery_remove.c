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
struct rx51_device_info {int /*<<< orphan*/  channel_temp; int /*<<< orphan*/  channel_bsi; int /*<<< orphan*/  channel_vbat; int /*<<< orphan*/  bat; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ ) ; 
 struct rx51_device_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx51_battery_remove(struct platform_device *pdev)
{
	struct rx51_device_info *di = platform_get_drvdata(pdev);

	power_supply_unregister(di->bat);

	iio_channel_release(di->channel_vbat);
	iio_channel_release(di->channel_bsi);
	iio_channel_release(di->channel_temp);

	return 0;
}