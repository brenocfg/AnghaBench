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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ina3221_data {int /*<<< orphan*/  reg_config; int /*<<< orphan*/  regmap; int /*<<< orphan*/  single_shot; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int INA3221_CHANNEL3 ; 
 int /*<<< orphan*/  INA3221_CONFIG ; 
 int INA3221_NUM_CHANNELS ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_in_enable 129 
#define  hwmon_in_input 128 
 int /*<<< orphan*/ * ina3221_in_reg ; 
 long ina3221_is_enabled (struct ina3221_data*,int) ; 
 int ina3221_read_value (struct ina3221_data*,int /*<<< orphan*/ ,int*) ; 
 int ina3221_wait_for_data (struct ina3221_data*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ina3221_read_in(struct device *dev, u32 attr, int channel, long *val)
{
	const bool is_shunt = channel > INA3221_CHANNEL3;
	struct ina3221_data *ina = dev_get_drvdata(dev);
	u8 reg = ina3221_in_reg[channel];
	int regval, ret;

	/* Translate shunt channel index to sensor channel index */
	channel %= INA3221_NUM_CHANNELS;

	switch (attr) {
	case hwmon_in_input:
		if (!ina3221_is_enabled(ina, channel))
			return -ENODATA;

		/* Write CONFIG register to trigger a single-shot measurement */
		if (ina->single_shot)
			regmap_write(ina->regmap, INA3221_CONFIG,
				     ina->reg_config);

		ret = ina3221_wait_for_data(ina);
		if (ret)
			return ret;

		ret = ina3221_read_value(ina, reg, &regval);
		if (ret)
			return ret;

		/*
		 * Scale of shunt voltage (uV): LSB is 40uV
		 * Scale of bus voltage (mV): LSB is 8mV
		 */
		*val = regval * (is_shunt ? 40 : 8);
		return 0;
	case hwmon_in_enable:
		*val = ina3221_is_enabled(ina, channel);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}