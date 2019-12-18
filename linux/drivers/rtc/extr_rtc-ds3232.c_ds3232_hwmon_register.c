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
struct ds3232 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RTC_DRV_DS3232_HWMON ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,char const*,struct ds3232*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds3232_hwmon_chip_info ; 

__attribute__((used)) static void ds3232_hwmon_register(struct device *dev, const char *name)
{
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	struct device *hwmon_dev;

	if (!IS_ENABLED(CONFIG_RTC_DRV_DS3232_HWMON))
		return;

	hwmon_dev = devm_hwmon_device_register_with_info(dev, name, ds3232,
							&ds3232_hwmon_chip_info,
							NULL);
	if (IS_ERR(hwmon_dev)) {
		dev_err(dev, "unable to register hwmon device %ld\n",
			PTR_ERR(hwmon_dev));
	}
}