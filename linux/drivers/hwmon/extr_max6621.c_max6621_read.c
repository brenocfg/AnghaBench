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
typedef  long u32 ;
struct max6621_data {int* input_chan2reg; int /*<<< orphan*/  client; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  long s8 ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 long MAX6621_ALERT_DIS ; 
 int /*<<< orphan*/  MAX6621_CLEAR_ALERT_REG ; 
 int MAX6621_CONFIG2_REG ; 
 long MAX6621_REG_TEMP_SHIFT ; 
 int MAX6621_TEMP_ALERT_CAUSE_REG ; 
 int MAX6621_TEMP_ALERT_CHAN_SHIFT ; 
 struct max6621_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp 132 
#define  hwmon_temp_crit 131 
#define  hwmon_temp_crit_alarm 130 
#define  hwmon_temp_input 129 
#define  hwmon_temp_offset 128 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* max6621_temp_alert_chan2reg ; 
 int max6621_verify_reg_data (struct device*,long) ; 
 int regmap_read (int /*<<< orphan*/ ,int,long*) ; 

__attribute__((used)) static int
max6621_read(struct device *dev, enum hwmon_sensor_types type, u32 attr,
	     int channel, long *val)
{
	struct max6621_data *data = dev_get_drvdata(dev);
	u32 regval;
	int reg;
	s8 temp;
	int ret;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			reg = data->input_chan2reg[channel];
			ret = regmap_read(data->regmap, reg, &regval);
			if (ret)
				return ret;

			ret = max6621_verify_reg_data(dev, regval);
			if (ret)
				return ret;

			/*
			 * Bit MAX6621_REG_TEMP_SHIFT represents 1 degree step.
			 * The temperature is given in two's complement and 8
			 * bits is used for the register conversion.
			 */
			temp = (regval >> MAX6621_REG_TEMP_SHIFT);
			*val = temp * 1000L;

			break;
		case hwmon_temp_offset:
			ret = regmap_read(data->regmap, MAX6621_CONFIG2_REG,
					  &regval);
			if (ret)
				return ret;

			ret = max6621_verify_reg_data(dev, regval);
			if (ret)
				return ret;

			*val = (regval >> MAX6621_REG_TEMP_SHIFT) *
			       1000L;

			break;
		case hwmon_temp_crit:
			channel -= MAX6621_TEMP_ALERT_CHAN_SHIFT;
			reg = max6621_temp_alert_chan2reg[channel];
			ret = regmap_read(data->regmap, reg, &regval);
			if (ret)
				return ret;

			ret = max6621_verify_reg_data(dev, regval);
			if (ret)
				return ret;

			*val = regval * 1000L;

			break;
		case hwmon_temp_crit_alarm:
			/*
			 * Set val to zero to recover the case, when reading
			 * MAX6621_TEMP_ALERT_CAUSE_REG results in for example
			 * MAX6621_ALERT_DIS. Reading will return with error,
			 * but in such case alarm should be returned as 0.
			 */
			*val = 0;
			ret = regmap_read(data->regmap,
					  MAX6621_TEMP_ALERT_CAUSE_REG,
					  &regval);
			if (ret)
				return ret;

			ret = max6621_verify_reg_data(dev, regval);
			if (ret) {
				/* Do not report error if alert is disabled. */
				if (regval == MAX6621_ALERT_DIS)
					return 0;
				else
					return ret;
			}

			/*
			 * Clear the alert automatically, using send-byte
			 * smbus protocol for clearing alert.
			 */
			if (regval) {
				ret = i2c_smbus_write_byte(data->client,
						MAX6621_CLEAR_ALERT_REG);
				if (ret)
					return ret;
			}

			*val = !!regval;

			break;
		default:
			return -EOPNOTSUPP;
		}
		break;

	default:
		return -EOPNOTSUPP;
	}

	return 0;
}