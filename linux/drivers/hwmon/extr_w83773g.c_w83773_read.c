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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct regmap* dev_get_drvdata (struct device*) ; 
 int get_fault (struct regmap*,int,long*) ; 
 int get_local_temp (struct regmap*,long*) ; 
 int get_offset (struct regmap*,int,long*) ; 
 int get_remote_temp (struct regmap*,int,long*) ; 
 int get_update_interval (struct regmap*,long*) ; 
 int hwmon_chip ; 
 int hwmon_chip_update_interval ; 
#define  hwmon_temp_fault 130 
#define  hwmon_temp_input 129 
#define  hwmon_temp_offset 128 

__attribute__((used)) static int w83773_read(struct device *dev, enum hwmon_sensor_types type,
		       u32 attr, int channel, long *val)
{
	struct regmap *regmap = dev_get_drvdata(dev);

	if (type == hwmon_chip) {
		if (attr == hwmon_chip_update_interval)
			return get_update_interval(regmap, val);
		return -EOPNOTSUPP;
	}

	switch (attr) {
	case hwmon_temp_input:
		if (channel == 0)
			return get_local_temp(regmap, val);
		return get_remote_temp(regmap, channel - 1, val);
	case hwmon_temp_fault:
		return get_fault(regmap, channel - 1, val);
	case hwmon_temp_offset:
		return get_offset(regmap, channel - 1, val);
	default:
		return -EOPNOTSUPP;
	}
}