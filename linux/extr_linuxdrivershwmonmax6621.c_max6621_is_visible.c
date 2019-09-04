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
struct max6621_data {scalar_t__* input_chan2reg; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
#define  hwmon_temp 133 
#define  hwmon_temp_crit 132 
#define  hwmon_temp_crit_alarm 131 
#define  hwmon_temp_input 130 
#define  hwmon_temp_label 129 
#define  hwmon_temp_offset 128 

__attribute__((used)) static umode_t
max6621_is_visible(const void *data, enum hwmon_sensor_types type, u32 attr,
		   int channel)
{
	/* Skip channels which are not physically conncted. */
	if (((struct max6621_data *)data)->input_chan2reg[channel] < 0)
		return 0;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_label:
		case hwmon_temp_crit_alarm:
			return 0444;
		case hwmon_temp_offset:
		case hwmon_temp_crit:
			return 0644;
		default:
			break;
		}

	default:
		break;
	}

	return 0;
}