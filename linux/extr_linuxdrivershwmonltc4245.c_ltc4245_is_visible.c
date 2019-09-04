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
struct ltc4245_data {int /*<<< orphan*/  use_extra_gpios; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
#define  hwmon_curr 135 
#define  hwmon_curr_input 134 
#define  hwmon_curr_max_alarm 133 
#define  hwmon_in 132 
#define  hwmon_in_input 131 
#define  hwmon_in_min_alarm 130 
#define  hwmon_power 129 
#define  hwmon_power_input 128 

__attribute__((used)) static umode_t ltc4245_is_visible(const void *_data,
				  enum hwmon_sensor_types type,
				  u32 attr, int channel)
{
	const struct ltc4245_data *data = _data;

	switch (type) {
	case hwmon_in:
		if (channel == 0)
			return 0;
		switch (attr) {
		case hwmon_in_input:
			if (channel > 9 && !data->use_extra_gpios)
				return 0;
			return S_IRUGO;
		case hwmon_in_min_alarm:
			if (channel > 8)
				return 0;
			return S_IRUGO;
		default:
			return 0;
		}
	case hwmon_curr:
		switch (attr) {
		case hwmon_curr_input:
		case hwmon_curr_max_alarm:
			return S_IRUGO;
		default:
			return 0;
		}
	case hwmon_power:
		switch (attr) {
		case hwmon_power_input:
			return S_IRUGO;
		default:
			return 0;
		}
	default:
		return 0;
	}
}