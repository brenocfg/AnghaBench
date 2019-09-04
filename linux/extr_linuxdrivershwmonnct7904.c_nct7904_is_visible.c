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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
#define  hwmon_fan 131 
#define  hwmon_in 130 
#define  hwmon_pwm 129 
#define  hwmon_temp 128 
 int /*<<< orphan*/  nct7904_fan_is_visible (void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nct7904_in_is_visible (void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nct7904_pwm_is_visible (void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nct7904_temp_is_visible (void const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static umode_t nct7904_is_visible(const void *data,
				  enum hwmon_sensor_types type,
				  u32 attr, int channel)
{
	switch (type) {
	case hwmon_in:
		return nct7904_in_is_visible(data, attr, channel);
	case hwmon_fan:
		return nct7904_fan_is_visible(data, attr, channel);
	case hwmon_pwm:
		return nct7904_pwm_is_visible(data, attr, channel);
	case hwmon_temp:
		return nct7904_temp_is_visible(data, attr, channel);
	default:
		return 0;
	}
}