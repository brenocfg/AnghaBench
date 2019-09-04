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
typedef  int u32 ;
struct lm75_data {int resolution_limits; int resolution; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 int EINVAL ; 
 int LM75_REG_HYST ; 
 int LM75_REG_MAX ; 
 int /*<<< orphan*/  LM75_TEMP_MAX ; 
 int /*<<< orphan*/  LM75_TEMP_MIN ; 
 long clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lm75_data* dev_get_drvdata (struct device*) ; 
 int hwmon_temp ; 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 
 int regmap_write (int /*<<< orphan*/ ,int,long) ; 

__attribute__((used)) static int lm75_write(struct device *dev, enum hwmon_sensor_types type,
		      u32 attr, int channel, long temp)
{
	struct lm75_data *data = dev_get_drvdata(dev);
	u8 resolution;
	int reg;

	if (type != hwmon_temp)
		return -EINVAL;

	switch (attr) {
	case hwmon_temp_max:
		reg = LM75_REG_MAX;
		break;
	case hwmon_temp_max_hyst:
		reg = LM75_REG_HYST;
		break;
	default:
		return -EINVAL;
	}

	/*
	 * Resolution of limit registers is assumed to be the same as the
	 * temperature input register resolution unless given explicitly.
	 */
	if (data->resolution_limits)
		resolution = data->resolution_limits;
	else
		resolution = data->resolution;

	temp = clamp_val(temp, LM75_TEMP_MIN, LM75_TEMP_MAX);
	temp = DIV_ROUND_CLOSEST(temp  << (resolution - 8),
				 1000) << (16 - resolution);

	return regmap_write(data->regmap, reg, temp);
}