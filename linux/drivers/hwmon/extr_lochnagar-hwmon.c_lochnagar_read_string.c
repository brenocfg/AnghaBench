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
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  hwmon_curr 130 
#define  hwmon_in 129 
#define  hwmon_power 128 
 char** lochnagar_chan_names ; 

__attribute__((used)) static int lochnagar_read_string(struct device *dev,
				 enum hwmon_sensor_types type, u32 attr,
				 int chan, const char **str)
{
	switch (type) {
	case hwmon_in:
	case hwmon_curr:
	case hwmon_power:
		*str = lochnagar_chan_names[chan];
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}