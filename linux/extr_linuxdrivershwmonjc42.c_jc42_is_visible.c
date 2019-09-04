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
typedef  int u32 ;
struct jc42_data {unsigned int config; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 unsigned int JC42_CFG_EVENT_LOCK ; 
 unsigned int JC42_CFG_TCRIT_LOCK ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 
#define  hwmon_temp_crit 136 
#define  hwmon_temp_crit_alarm 135 
#define  hwmon_temp_crit_hyst 134 
#define  hwmon_temp_input 133 
#define  hwmon_temp_max 132 
#define  hwmon_temp_max_alarm 131 
#define  hwmon_temp_max_hyst 130 
#define  hwmon_temp_min 129 
#define  hwmon_temp_min_alarm 128 

__attribute__((used)) static umode_t jc42_is_visible(const void *_data, enum hwmon_sensor_types type,
			       u32 attr, int channel)
{
	const struct jc42_data *data = _data;
	unsigned int config = data->config;
	umode_t mode = S_IRUGO;

	switch (attr) {
	case hwmon_temp_min:
	case hwmon_temp_max:
		if (!(config & JC42_CFG_EVENT_LOCK))
			mode |= S_IWUSR;
		break;
	case hwmon_temp_crit:
		if (!(config & JC42_CFG_TCRIT_LOCK))
			mode |= S_IWUSR;
		break;
	case hwmon_temp_crit_hyst:
		if (!(config & (JC42_CFG_EVENT_LOCK | JC42_CFG_TCRIT_LOCK)))
			mode |= S_IWUSR;
		break;
	case hwmon_temp_input:
	case hwmon_temp_max_hyst:
	case hwmon_temp_min_alarm:
	case hwmon_temp_max_alarm:
	case hwmon_temp_crit_alarm:
		break;
	default:
		mode = 0;
		break;
	}
	return mode;
}