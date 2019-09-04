#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  connected; } ;
struct mlxreg_fan {TYPE_2__ pwm; TYPE_1__* tacho; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;
struct TYPE_3__ {int /*<<< orphan*/  connected; } ;

/* Variables and functions */
#define  hwmon_fan 132 
#define  hwmon_fan_fault 131 
#define  hwmon_fan_input 130 
#define  hwmon_pwm 129 
#define  hwmon_pwm_input 128 

__attribute__((used)) static umode_t
mlxreg_fan_is_visible(const void *data, enum hwmon_sensor_types type, u32 attr,
		      int channel)
{
	switch (type) {
	case hwmon_fan:
		if (!(((struct mlxreg_fan *)data)->tacho[channel].connected))
			return 0;

		switch (attr) {
		case hwmon_fan_input:
		case hwmon_fan_fault:
			return 0444;
		default:
			break;
		}
		break;

	case hwmon_pwm:
		if (!(((struct mlxreg_fan *)data)->pwm.connected))
			return 0;

		switch (attr) {
		case hwmon_pwm_input:
			return 0644;
		default:
			break;
		}
		break;

	default:
		break;
	}

	return 0;
}