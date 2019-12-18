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
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ds3232_hwmon_read_temp (struct device*,long*) ; 
#define  hwmon_temp_input 128 

__attribute__((used)) static int ds3232_hwmon_read(struct device *dev,
			     enum hwmon_sensor_types type,
			     u32 attr, int channel, long *temp)
{
	int err;

	switch (attr) {
	case hwmon_temp_input:
		err = ds3232_hwmon_read_temp(dev, temp);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}