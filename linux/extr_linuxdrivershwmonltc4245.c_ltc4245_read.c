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
 int ltc4245_read_curr (struct device*,int /*<<< orphan*/ ,int,long*) ; 
 int ltc4245_read_in (struct device*,int /*<<< orphan*/ ,int,long*) ; 
 int ltc4245_read_power (struct device*,int /*<<< orphan*/ ,int,long*) ; 

__attribute__((used)) static int ltc4245_read(struct device *dev, enum hwmon_sensor_types type,
			u32 attr, int channel, long *val)
{

	switch (type) {
	case hwmon_curr:
		return ltc4245_read_curr(dev, attr, channel, val);
	case hwmon_power:
		return ltc4245_read_power(dev, attr, channel, val);
	case hwmon_in:
		return ltc4245_read_in(dev, attr, channel - 1, val);
	default:
		return -EOPNOTSUPP;
	}
}