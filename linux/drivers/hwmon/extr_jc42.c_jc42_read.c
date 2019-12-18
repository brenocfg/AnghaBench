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
struct jc42_data {int* temp; size_t config; } ;
struct device {int dummy; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct jc42_data*) ; 
 int JC42_ALARM_CRIT_BIT ; 
 int JC42_ALARM_MAX_BIT ; 
 int JC42_ALARM_MIN_BIT ; 
 size_t JC42_CFG_HYST_MASK ; 
 size_t JC42_CFG_HYST_SHIFT ; 
 int PTR_ERR (struct jc42_data*) ; 
#define  hwmon_temp_crit 136 
#define  hwmon_temp_crit_alarm 135 
#define  hwmon_temp_crit_hyst 134 
#define  hwmon_temp_input 133 
#define  hwmon_temp_max 132 
#define  hwmon_temp_max_alarm 131 
#define  hwmon_temp_max_hyst 130 
#define  hwmon_temp_min 129 
#define  hwmon_temp_min_alarm 128 
 int* jc42_hysteresis ; 
 void* jc42_temp_from_reg (int) ; 
 struct jc42_data* jc42_update_device (struct device*) ; 
 size_t t_crit ; 
 size_t t_input ; 
 size_t t_max ; 
 size_t t_min ; 

__attribute__((used)) static int jc42_read(struct device *dev, enum hwmon_sensor_types type,
		     u32 attr, int channel, long *val)
{
	struct jc42_data *data = jc42_update_device(dev);
	int temp, hyst;

	if (IS_ERR(data))
		return PTR_ERR(data);

	switch (attr) {
	case hwmon_temp_input:
		*val = jc42_temp_from_reg(data->temp[t_input]);
		return 0;
	case hwmon_temp_min:
		*val = jc42_temp_from_reg(data->temp[t_min]);
		return 0;
	case hwmon_temp_max:
		*val = jc42_temp_from_reg(data->temp[t_max]);
		return 0;
	case hwmon_temp_crit:
		*val = jc42_temp_from_reg(data->temp[t_crit]);
		return 0;
	case hwmon_temp_max_hyst:
		temp = jc42_temp_from_reg(data->temp[t_max]);
		hyst = jc42_hysteresis[(data->config & JC42_CFG_HYST_MASK)
						>> JC42_CFG_HYST_SHIFT];
		*val = temp - hyst;
		return 0;
	case hwmon_temp_crit_hyst:
		temp = jc42_temp_from_reg(data->temp[t_crit]);
		hyst = jc42_hysteresis[(data->config & JC42_CFG_HYST_MASK)
						>> JC42_CFG_HYST_SHIFT];
		*val = temp - hyst;
		return 0;
	case hwmon_temp_min_alarm:
		*val = (data->temp[t_input] >> JC42_ALARM_MIN_BIT) & 1;
		return 0;
	case hwmon_temp_max_alarm:
		*val = (data->temp[t_input] >> JC42_ALARM_MAX_BIT) & 1;
		return 0;
	case hwmon_temp_crit_alarm:
		*val = (data->temp[t_input] >> JC42_ALARM_CRIT_BIT) & 1;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}