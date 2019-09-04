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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct adt7411_data {int /*<<< orphan*/  use_ext_temp; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
#define  hwmon_in 139 
#define  hwmon_in_alarm 138 
#define  hwmon_in_input 137 
#define  hwmon_in_max 136 
#define  hwmon_in_min 135 
#define  hwmon_temp 134 
#define  hwmon_temp_fault 133 
#define  hwmon_temp_input 132 
#define  hwmon_temp_max 131 
#define  hwmon_temp_max_alarm 130 
#define  hwmon_temp_min 129 
#define  hwmon_temp_min_alarm 128 

__attribute__((used)) static umode_t adt7411_is_visible(const void *_data,
				  enum hwmon_sensor_types type,
				  u32 attr, int channel)
{
	const struct adt7411_data *data = _data;
	bool visible;

	switch (type) {
	case hwmon_in:
		visible = channel == 0 || channel >= 3 || !data->use_ext_temp;
		switch (attr) {
		case hwmon_in_input:
		case hwmon_in_alarm:
			return visible ? S_IRUGO : 0;
		case hwmon_in_min:
		case hwmon_in_max:
			return visible ? S_IRUGO | S_IWUSR : 0;
		}
		break;
	case hwmon_temp:
		visible = channel == 0 || data->use_ext_temp;
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_min_alarm:
		case hwmon_temp_max_alarm:
		case hwmon_temp_fault:
			return visible ? S_IRUGO : 0;
		case hwmon_temp_min:
		case hwmon_temp_max:
			return visible ? S_IRUGO | S_IWUSR : 0;
		}
		break;
	default:
		break;
	}
	return 0;
}