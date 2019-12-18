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
struct ina3221_input {int /*<<< orphan*/  label; } ;
struct ina3221_data {struct ina3221_input* inputs; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int INA3221_CHANNEL3 ; 
#define  hwmon_chip 140 
#define  hwmon_chip_samples 139 
#define  hwmon_chip_update_interval 138 
#define  hwmon_curr 137 
#define  hwmon_curr_crit 136 
#define  hwmon_curr_crit_alarm 135 
#define  hwmon_curr_input 134 
#define  hwmon_curr_max 133 
#define  hwmon_curr_max_alarm 132 
#define  hwmon_in 131 
#define  hwmon_in_enable 130 
#define  hwmon_in_input 129 
#define  hwmon_in_label 128 

__attribute__((used)) static umode_t ina3221_is_visible(const void *drvdata,
				  enum hwmon_sensor_types type,
				  u32 attr, int channel)
{
	const struct ina3221_data *ina = drvdata;
	const struct ina3221_input *input = NULL;

	switch (type) {
	case hwmon_chip:
		switch (attr) {
		case hwmon_chip_samples:
		case hwmon_chip_update_interval:
			return 0644;
		default:
			return 0;
		}
	case hwmon_in:
		/* Ignore in0_ */
		if (channel == 0)
			return 0;

		switch (attr) {
		case hwmon_in_label:
			if (channel - 1 <= INA3221_CHANNEL3)
				input = &ina->inputs[channel - 1];
			/* Hide label node if label is not provided */
			return (input && input->label) ? 0444 : 0;
		case hwmon_in_input:
			return 0444;
		case hwmon_in_enable:
			return 0644;
		default:
			return 0;
		}
	case hwmon_curr:
		switch (attr) {
		case hwmon_curr_input:
		case hwmon_curr_crit_alarm:
		case hwmon_curr_max_alarm:
			return 0444;
		case hwmon_curr_crit:
		case hwmon_curr_max:
			return 0644;
		default:
			return 0;
		}
	default:
		return 0;
	}
}