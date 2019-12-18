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
struct ina3221_data {int reg_config; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INA3221_CONFIG ; 
 int INA3221_CONFIG_AVG_MASK ; 
 int INA3221_CONFIG_AVG_SHIFT ; 
 int INA3221_CONFIG_VBUS_CT_MASK ; 
 int INA3221_CONFIG_VBUS_CT_SHIFT ; 
 int INA3221_CONFIG_VSH_CT_MASK ; 
 int INA3221_CONFIG_VSH_CT_SHIFT ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
 int find_closest (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  hwmon_chip_samples 129 
#define  hwmon_chip_update_interval 128 
 int /*<<< orphan*/  ina3221_avg_samples ; 
 int /*<<< orphan*/  ina3221_conv_time ; 
 int ina3221_interval_ms_to_conv_time (int,long) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ina3221_write_chip(struct device *dev, u32 attr, long val)
{
	struct ina3221_data *ina = dev_get_drvdata(dev);
	int ret, idx;
	u32 tmp;

	switch (attr) {
	case hwmon_chip_samples:
		idx = find_closest(val, ina3221_avg_samples,
				   ARRAY_SIZE(ina3221_avg_samples));

		tmp = (ina->reg_config & ~INA3221_CONFIG_AVG_MASK) |
		      (idx << INA3221_CONFIG_AVG_SHIFT);
		ret = regmap_write(ina->regmap, INA3221_CONFIG, tmp);
		if (ret)
			return ret;

		/* Update reg_config accordingly */
		ina->reg_config = tmp;
		return 0;
	case hwmon_chip_update_interval:
		tmp = ina3221_interval_ms_to_conv_time(ina->reg_config, val);
		idx = find_closest(tmp, ina3221_conv_time,
				   ARRAY_SIZE(ina3221_conv_time));

		/* Update Bus and Shunt voltage conversion times */
		tmp = INA3221_CONFIG_VBUS_CT_MASK | INA3221_CONFIG_VSH_CT_MASK;
		tmp = (ina->reg_config & ~tmp) |
		      (idx << INA3221_CONFIG_VBUS_CT_SHIFT) |
		      (idx << INA3221_CONFIG_VSH_CT_SHIFT);
		ret = regmap_write(ina->regmap, INA3221_CONFIG, tmp);
		if (ret)
			return ret;

		/* Update reg_config accordingly */
		ina->reg_config = tmp;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}