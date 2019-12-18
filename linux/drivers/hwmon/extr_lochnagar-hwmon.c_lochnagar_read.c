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
struct lochnagar_hwmon {int* power_nsamples; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (int,int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LN2_CURR ; 
 int /*<<< orphan*/  LN2_CURR_UNITS ; 
 int LN2_SAMPLE_US ; 
 int /*<<< orphan*/  LN2_TEMP ; 
 int /*<<< orphan*/  LN2_TEMP_UNITS ; 
 int /*<<< orphan*/  LN2_VOLT ; 
 int /*<<< orphan*/  LN2_VOLT_UNITS ; 
 struct lochnagar_hwmon* dev_get_drvdata (struct device*) ; 
#define  hwmon_curr 133 
#define  hwmon_in 132 
#define  hwmon_power 131 
#define  hwmon_power_average 130 
#define  hwmon_power_average_interval 129 
#define  hwmon_temp 128 
 int read_power (struct device*,int,long*) ; 
 int read_sensor (struct device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,long*) ; 

__attribute__((used)) static int lochnagar_read(struct device *dev, enum hwmon_sensor_types type,
			  u32 attr, int chan, long *val)
{
	struct lochnagar_hwmon *priv = dev_get_drvdata(dev);
	int interval;

	switch (type) {
	case hwmon_in:
		return read_sensor(dev, chan, LN2_VOLT, 1, LN2_VOLT_UNITS, val);
	case hwmon_curr:
		return read_sensor(dev, chan, LN2_CURR, 1, LN2_CURR_UNITS, val);
	case hwmon_temp:
		return read_sensor(dev, chan, LN2_TEMP, 1, LN2_TEMP_UNITS, val);
	case hwmon_power:
		switch (attr) {
		case hwmon_power_average:
			return read_power(dev, chan, val);
		case hwmon_power_average_interval:
			interval = priv->power_nsamples[chan] * LN2_SAMPLE_US;
			*val = DIV_ROUND_CLOSEST(interval, 1000);
			return 0;
		default:
			return -EOPNOTSUPP;
		}
	default:
		return -EOPNOTSUPP;
	}
}