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
struct ina3221_data {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_chip 130 
#define  hwmon_curr 129 
#define  hwmon_in 128 
 int ina3221_write_chip (struct device*,int /*<<< orphan*/ ,long) ; 
 int ina3221_write_curr (struct device*,int /*<<< orphan*/ ,int,long) ; 
 int ina3221_write_enable (struct device*,int,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ina3221_write(struct device *dev, enum hwmon_sensor_types type,
			 u32 attr, int channel, long val)
{
	struct ina3221_data *ina = dev_get_drvdata(dev);
	int ret;

	mutex_lock(&ina->lock);

	switch (type) {
	case hwmon_chip:
		ret = ina3221_write_chip(dev, attr, val);
		break;
	case hwmon_in:
		/* 0-align channel ID */
		ret = ina3221_write_enable(dev, channel - 1, val);
		break;
	case hwmon_curr:
		ret = ina3221_write_curr(dev, attr, channel, val);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

	mutex_unlock(&ina->lock);

	return ret;
}