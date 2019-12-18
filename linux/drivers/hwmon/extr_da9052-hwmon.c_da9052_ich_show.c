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
struct da9052_hwmon {int /*<<< orphan*/  da9052; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_ICHG_AV_REG ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int da9052_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9052_hwmon* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t da9052_ich_show(struct device *dev,
			       struct device_attribute *devattr, char *buf)
{
	struct da9052_hwmon *hwmon = dev_get_drvdata(dev);
	int ret;

	ret = da9052_reg_read(hwmon->da9052, DA9052_ICHG_AV_REG);
	if (ret < 0)
		return ret;

	/* Equivalent to 3.9mA/bit in register ICHG_AV */
	return sprintf(buf, "%d\n", DIV_ROUND_CLOSEST(ret * 39, 10));
}