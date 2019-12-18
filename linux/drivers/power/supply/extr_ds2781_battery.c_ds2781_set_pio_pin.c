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
struct power_supply {int dummy; } ;
struct ds2781_device_info {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS2781_SFR ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ds2781_write (struct ds2781_device_info*,int*,int /*<<< orphan*/ ,int) ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 struct ds2781_device_info* to_ds2781_device_info (struct power_supply*) ; 
 struct power_supply* to_power_supply (struct device*) ; 

__attribute__((used)) static ssize_t ds2781_set_pio_pin(struct device *dev,
	struct device_attribute *attr,
	const char *buf,
	size_t count)
{
	int ret;
	u8 new_setting;
	struct power_supply *psy = to_power_supply(dev);
	struct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = kstrtou8(buf, 0, &new_setting);
	if (ret < 0)
		return ret;

	if ((new_setting != 0) && (new_setting != 1)) {
		dev_err(dev_info->dev, "Invalid pio_pin setting (0 or 1)\n");
		return -EINVAL;
	}

	ret = ds2781_write(dev_info, &new_setting,
				DS2781_SFR, sizeof(u8));
	if (ret < 0)
		return ret;

	return count;
}