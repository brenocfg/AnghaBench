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
struct tmp102 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int TMP102_THIGH_REG ; 
 int TMP102_TLOW_REG ; 
 long clamp_val (long,int,int) ; 
 struct tmp102* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 
 int regmap_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmp102_mC_to_reg (long) ; 

__attribute__((used)) static int tmp102_write(struct device *dev, enum hwmon_sensor_types type,
			u32 attr, int channel, long temp)
{
	struct tmp102 *tmp102 = dev_get_drvdata(dev);
	int reg;

	switch (attr) {
	case hwmon_temp_max_hyst:
		reg = TMP102_TLOW_REG;
		break;
	case hwmon_temp_max:
		reg = TMP102_THIGH_REG;
		break;
	default:
		return -EOPNOTSUPP;
	}

	temp = clamp_val(temp, -256000, 255000);
	return regmap_write(tmp102->regmap, reg, tmp102_mC_to_reg(temp));
}