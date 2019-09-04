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
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_GPHY1_CR ; 
 int EOPNOTSUPP ; 
#define  hwmon_temp_input 128 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_read(struct device *dev, enum hwmon_sensor_types type,
		    u32 attr, int channel, long *temp)
{
	int value;

	switch (attr) {
	case hwmon_temp_input:
		/* get the temperature including one decimal place */
		value = (ltq_cgu_r32(CGU_GPHY1_CR) >> 9) & 0x01FF;
		value = value * 5;
		/* range -38 to +154 °C, register value zero is -38.0 °C */
		value -= 380;
		/* scale temp to millidegree */
		value = value * 100;
		break;
	default:
		return -EOPNOTSUPP;
	}

	*temp = value;
	return 0;
}