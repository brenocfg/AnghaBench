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
typedef  int /*<<< orphan*/  u32 ;
struct ntc_data {int dummy; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EINVAL ; 
 struct ntc_data* dev_get_drvdata (struct device*) ; 
 long get_temp_mc (struct ntc_data*,int) ; 
#define  hwmon_temp 130 
#define  hwmon_temp_input 129 
#define  hwmon_temp_type 128 
 int ntc_thermistor_get_ohm (struct ntc_data*) ; 

__attribute__((used)) static int ntc_read(struct device *dev, enum hwmon_sensor_types type,
		    u32 attr, int channel, long *val)
{
	struct ntc_data *data = dev_get_drvdata(dev);
	int ohm;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			ohm = ntc_thermistor_get_ohm(data);
			if (ohm < 0)
				return ohm;
			*val = get_temp_mc(data, ohm);
			return 0;
		case hwmon_temp_type:
			*val = 4;
			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return -EINVAL;
}