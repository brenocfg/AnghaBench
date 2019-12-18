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
typedef  int u16 ;
struct power_supply {int dummy; } ;
struct ds2780_device_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ds2780_get_rsgain_register (struct ds2780_device_info*,int*) ; 
 int sprintf (char*,char*,int) ; 
 struct ds2780_device_info* to_ds2780_device_info (struct power_supply*) ; 
 struct power_supply* to_power_supply (struct device*) ; 

__attribute__((used)) static ssize_t ds2780_get_rsgain_setting(struct device *dev,
	struct device_attribute *attr,
	char *buf)
{
	int ret;
	u16 rsgain;
	struct power_supply *psy = to_power_supply(dev);
	struct ds2780_device_info *dev_info = to_ds2780_device_info(psy);

	ret = ds2780_get_rsgain_register(dev_info, &rsgain);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", rsgain);
}