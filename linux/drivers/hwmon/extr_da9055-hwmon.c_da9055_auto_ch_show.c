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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct da9055_hwmon {int /*<<< orphan*/  hwmon_lock; int /*<<< orphan*/  da9055; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ DA9055_REG_VSYS_RES ; 
 int da9055_disable_auto_mode (int /*<<< orphan*/ ,int) ; 
 int da9055_enable_auto_mode (int /*<<< orphan*/ ,int) ; 
 int da9055_reg_read (int /*<<< orphan*/ ,scalar_t__) ; 
 struct da9055_hwmon* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int volt_reg_to_mv (int,int) ; 

__attribute__((used)) static ssize_t da9055_auto_ch_show(struct device *dev,
				   struct device_attribute *devattr,
				   char *buf)
{
	struct da9055_hwmon *hwmon = dev_get_drvdata(dev);
	int ret, adc;
	int channel = to_sensor_dev_attr(devattr)->index;

	mutex_lock(&hwmon->hwmon_lock);

	ret = da9055_enable_auto_mode(hwmon->da9055, channel);
	if (ret < 0)
		goto hwmon_err;

	usleep_range(10000, 10500);

	adc = da9055_reg_read(hwmon->da9055, DA9055_REG_VSYS_RES + channel);
	if (adc < 0) {
		ret = adc;
		goto hwmon_err_release;
	}

	ret = da9055_disable_auto_mode(hwmon->da9055, channel);
	if (ret < 0)
		goto hwmon_err;

	mutex_unlock(&hwmon->hwmon_lock);

	return sprintf(buf, "%d\n", volt_reg_to_mv(adc, channel));

hwmon_err_release:
	da9055_disable_auto_mode(hwmon->da9055, channel);
hwmon_err:
	mutex_unlock(&hwmon->hwmon_lock);
	return ret;
}