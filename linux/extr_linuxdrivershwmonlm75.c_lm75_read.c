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
struct lm75_data {long sample_time; int /*<<< orphan*/  resolution; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EINVAL ; 
 int LM75_REG_HYST ; 
 int LM75_REG_MAX ; 
 int LM75_REG_TEMP ; 
 struct lm75_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_chip 133 
#define  hwmon_chip_update_interval 132 
#define  hwmon_temp 131 
#define  hwmon_temp_input 130 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 
 long lm75_reg_to_mc (unsigned int,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int lm75_read(struct device *dev, enum hwmon_sensor_types type,
		     u32 attr, int channel, long *val)
{
	struct lm75_data *data = dev_get_drvdata(dev);
	unsigned int regval;
	int err, reg;

	switch (type) {
	case hwmon_chip:
		switch (attr) {
		case hwmon_chip_update_interval:
			*val = data->sample_time;
			break;
		default:
			return -EINVAL;
		}
		break;
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			reg = LM75_REG_TEMP;
			break;
		case hwmon_temp_max:
			reg = LM75_REG_MAX;
			break;
		case hwmon_temp_max_hyst:
			reg = LM75_REG_HYST;
			break;
		default:
			return -EINVAL;
		}
		err = regmap_read(data->regmap, reg, &regval);
		if (err < 0)
			return err;

		*val = lm75_reg_to_mc(regval, data->resolution);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}