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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct da9052_hwmon {int /*<<< orphan*/  hwmon_lock; int /*<<< orphan*/  da9052; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_VDD_RES_REG ; 
 int da9052_disable_vddout_channel (int /*<<< orphan*/ ) ; 
 int da9052_enable_vddout_channel (int /*<<< orphan*/ ) ; 
 int da9052_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9052_hwmon* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int volt_reg_to_mv (int) ; 

__attribute__((used)) static ssize_t da9052_vddout_show(struct device *dev,
				  struct device_attribute *devattr, char *buf)
{
	struct da9052_hwmon *hwmon = dev_get_drvdata(dev);
	int ret, vdd;

	mutex_lock(&hwmon->hwmon_lock);

	ret = da9052_enable_vddout_channel(hwmon->da9052);
	if (ret < 0)
		goto hwmon_err;

	vdd = da9052_reg_read(hwmon->da9052, DA9052_VDD_RES_REG);
	if (vdd < 0) {
		ret = vdd;
		goto hwmon_err_release;
	}

	ret = da9052_disable_vddout_channel(hwmon->da9052);
	if (ret < 0)
		goto hwmon_err;

	mutex_unlock(&hwmon->hwmon_lock);
	return sprintf(buf, "%d\n", volt_reg_to_mv(vdd));

hwmon_err_release:
	da9052_disable_vddout_channel(hwmon->da9052);
hwmon_err:
	mutex_unlock(&hwmon->hwmon_lock);
	return ret;
}