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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct ina3221_input {int shunt_resistor; } ;
struct ina3221_data {int /*<<< orphan*/ * fields; int /*<<< orphan*/  reg_config; int /*<<< orphan*/  regmap; int /*<<< orphan*/  single_shot; struct ina3221_input* inputs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (int,int) ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INA3221_CONFIG ; 
 struct ina3221_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_curr_crit 132 
#define  hwmon_curr_crit_alarm 131 
#define  hwmon_curr_input 130 
#define  hwmon_curr_max 129 
#define  hwmon_curr_max_alarm 128 
 size_t** ina3221_curr_reg ; 
 int /*<<< orphan*/  ina3221_is_enabled (struct ina3221_data*,int) ; 
 int ina3221_read_value (struct ina3221_data*,size_t,int*) ; 
 int ina3221_wait_for_data (struct ina3221_data*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ina3221_read_curr(struct device *dev, u32 attr,
			     int channel, long *val)
{
	struct ina3221_data *ina = dev_get_drvdata(dev);
	struct ina3221_input *input = &ina->inputs[channel];
	int resistance_uo = input->shunt_resistor;
	u8 reg = ina3221_curr_reg[attr][channel];
	int regval, voltage_nv, ret;

	switch (attr) {
	case hwmon_curr_input:
		if (!ina3221_is_enabled(ina, channel))
			return -ENODATA;

		/* Write CONFIG register to trigger a single-shot measurement */
		if (ina->single_shot)
			regmap_write(ina->regmap, INA3221_CONFIG,
				     ina->reg_config);

		ret = ina3221_wait_for_data(ina);
		if (ret)
			return ret;

		/* fall through */
	case hwmon_curr_crit:
	case hwmon_curr_max:
		ret = ina3221_read_value(ina, reg, &regval);
		if (ret)
			return ret;

		/* Scale of shunt voltage: LSB is 40uV (40000nV) */
		voltage_nv = regval * 40000;
		/* Return current in mA */
		*val = DIV_ROUND_CLOSEST(voltage_nv, resistance_uo);
		return 0;
	case hwmon_curr_crit_alarm:
	case hwmon_curr_max_alarm:
		/* No actual register read if channel is disabled */
		if (!ina3221_is_enabled(ina, channel)) {
			/* Return 0 for alert flags */
			*val = 0;
			return 0;
		}
		ret = regmap_field_read(ina->fields[reg], &regval);
		if (ret)
			return ret;
		*val = regval;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}