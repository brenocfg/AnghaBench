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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct mlxreg_fan {TYPE_1__ pwm; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 long MLXREG_FAN_MAX_DUTY ; 
 long MLXREG_FAN_MIN_DUTY ; 
 struct mlxreg_fan* dev_get_drvdata (struct device*) ; 
#define  hwmon_pwm 129 
#define  hwmon_pwm_input 128 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int
mlxreg_fan_write(struct device *dev, enum hwmon_sensor_types type, u32 attr,
		 int channel, long val)
{
	struct mlxreg_fan *fan = dev_get_drvdata(dev);

	switch (type) {
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			if (val < MLXREG_FAN_MIN_DUTY ||
			    val > MLXREG_FAN_MAX_DUTY)
				return -EINVAL;
			return regmap_write(fan->regmap, fan->pwm.reg, val);
		default:
			return -EOPNOTSUPP;
		}
		break;

	default:
		return -EOPNOTSUPP;
	}

	return -EOPNOTSUPP;
}