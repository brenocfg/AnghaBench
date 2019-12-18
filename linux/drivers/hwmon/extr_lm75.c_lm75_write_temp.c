#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct lm75_data {int resolution; int /*<<< orphan*/  regmap; TYPE_1__* params; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int resolution_limits; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 int EINVAL ; 
 int LM75_REG_HYST ; 
 int LM75_REG_MAX ; 
 int /*<<< orphan*/  LM75_TEMP_MAX ; 
 int /*<<< orphan*/  LM75_TEMP_MIN ; 
 long clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lm75_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 
 int regmap_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm75_write_temp(struct device *dev, u32 attr, long temp)
{
	struct lm75_data *data = dev_get_drvdata(dev);
	u8 resolution;
	int reg;

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
	if (data->params->resolution_limits)
		resolution = data->params->resolution_limits;
	else
		resolution = data->resolution;

	temp = clamp_val(temp, LM75_TEMP_MIN, LM75_TEMP_MAX);
	temp = DIV_ROUND_CLOSEST(temp  << (resolution - 8),
				 1000) << (16 - resolution);

	return regmap_write(data->regmap, reg, (u16)temp);
}