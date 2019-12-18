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
struct tmp421_data {int config; int* temp; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int TMP421_CONFIG_RANGE ; 
#define  hwmon_temp_fault 129 
#define  hwmon_temp_input 128 
 long temp_from_s16 (int) ; 
 long temp_from_u16 (int) ; 
 struct tmp421_data* tmp421_update_device (struct device*) ; 

__attribute__((used)) static int tmp421_read(struct device *dev, enum hwmon_sensor_types type,
		       u32 attr, int channel, long *val)
{
	struct tmp421_data *tmp421 = tmp421_update_device(dev);

	switch (attr) {
	case hwmon_temp_input:
		if (tmp421->config & TMP421_CONFIG_RANGE)
			*val = temp_from_u16(tmp421->temp[channel]);
		else
			*val = temp_from_s16(tmp421->temp[channel]);
		return 0;
	case hwmon_temp_fault:
		/*
		 * The OPEN bit signals a fault. This is bit 0 of the temperature
		 * register (low byte).
		 */
		*val = tmp421->temp[channel] & 0x01;
		return 0;
	default:
		return -EOPNOTSUPP;
	}

}