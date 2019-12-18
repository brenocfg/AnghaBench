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
typedef  int /*<<< orphan*/  u8 ;
struct power_supply {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ab8500_fg {int /*<<< orphan*/  dev; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int /*<<< orphan*/  AB8505_RTC_PCUT_RESTART_REG ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int,int*) ; 
 struct ab8500_fg* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static ssize_t ab8505_powercut_restart_write(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	int ret;
	int reg_value;
	struct power_supply *psy = dev_get_drvdata(dev);
	struct ab8500_fg *di = power_supply_get_drvdata(psy);

	if (kstrtoint(buf, 10, &reg_value))
		goto fail;

	if (reg_value > 0xF) {
		dev_err(dev, "Incorrect parameter, echo 0 - 15 for number of restart\n");
		goto fail;
	}

	ret = abx500_set_register_interruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_RESTART_REG, (u8)reg_value);

	if (ret < 0)
		dev_err(dev, "Failed to set AB8505_RTC_PCUT_RESTART_REG\n");

fail:
	return count;

}