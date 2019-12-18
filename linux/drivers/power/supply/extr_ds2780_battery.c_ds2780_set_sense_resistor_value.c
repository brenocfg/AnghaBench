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
struct ds2780_device_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ds2780_set_sense_register (struct ds2780_device_info*,int /*<<< orphan*/ ) ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ds2780_device_info* to_ds2780_device_info (struct power_supply*) ; 
 struct power_supply* to_power_supply (struct device*) ; 

__attribute__((used)) static ssize_t ds2780_set_sense_resistor_value(struct device *dev,
	struct device_attribute *attr,
	const char *buf,
	size_t count)
{
	int ret;
	u8 new_setting;
	struct power_supply *psy = to_power_supply(dev);
	struct ds2780_device_info *dev_info = to_ds2780_device_info(psy);

	ret = kstrtou8(buf, 0, &new_setting);
	if (ret < 0)
		return ret;

	ret = ds2780_set_sense_register(dev_info, new_setting);
	if (ret < 0)
		return ret;

	return count;
}