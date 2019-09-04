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
struct lm90_data {int alarms; int /*<<< orphan*/  update_lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  REMOTE_OFFSET ; 
 struct lm90_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_crit 140 
#define  hwmon_temp_crit_alarm 139 
#define  hwmon_temp_crit_hyst 138 
#define  hwmon_temp_emergency 137 
#define  hwmon_temp_emergency_alarm 136 
#define  hwmon_temp_emergency_hyst 135 
#define  hwmon_temp_fault 134 
#define  hwmon_temp_input 133 
#define  hwmon_temp_max 132 
#define  hwmon_temp_max_alarm 131 
#define  hwmon_temp_min 130 
#define  hwmon_temp_min_alarm 129 
#define  hwmon_temp_offset 128 
 int* lm90_crit_alarm_bits ; 
 int* lm90_emergency_alarm_bits ; 
 int* lm90_fault_bits ; 
 long lm90_get_temp11 (struct lm90_data*,int /*<<< orphan*/ ) ; 
 long lm90_get_temp8 (struct lm90_data*,int /*<<< orphan*/ ) ; 
 long lm90_get_temphyst (struct lm90_data*,int /*<<< orphan*/ ) ; 
 int* lm90_max_alarm_bits ; 
 int* lm90_min_alarm_bits ; 
 int /*<<< orphan*/ * lm90_temp_crit_index ; 
 int /*<<< orphan*/ * lm90_temp_emerg_index ; 
 int /*<<< orphan*/ * lm90_temp_index ; 
 int /*<<< orphan*/ * lm90_temp_max_index ; 
 int /*<<< orphan*/ * lm90_temp_min_index ; 
 int lm90_update_device (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm90_temp_read(struct device *dev, u32 attr, int channel, long *val)
{
	struct lm90_data *data = dev_get_drvdata(dev);
	int err;

	mutex_lock(&data->update_lock);
	err = lm90_update_device(dev);
	mutex_unlock(&data->update_lock);
	if (err)
		return err;

	switch (attr) {
	case hwmon_temp_input:
		*val = lm90_get_temp11(data, lm90_temp_index[channel]);
		break;
	case hwmon_temp_min_alarm:
		*val = (data->alarms >> lm90_min_alarm_bits[channel]) & 1;
		break;
	case hwmon_temp_max_alarm:
		*val = (data->alarms >> lm90_max_alarm_bits[channel]) & 1;
		break;
	case hwmon_temp_crit_alarm:
		*val = (data->alarms >> lm90_crit_alarm_bits[channel]) & 1;
		break;
	case hwmon_temp_emergency_alarm:
		*val = (data->alarms >> lm90_emergency_alarm_bits[channel]) & 1;
		break;
	case hwmon_temp_fault:
		*val = (data->alarms >> lm90_fault_bits[channel]) & 1;
		break;
	case hwmon_temp_min:
		if (channel == 0)
			*val = lm90_get_temp8(data,
					      lm90_temp_min_index[channel]);
		else
			*val = lm90_get_temp11(data,
					       lm90_temp_min_index[channel]);
		break;
	case hwmon_temp_max:
		if (channel == 0)
			*val = lm90_get_temp8(data,
					      lm90_temp_max_index[channel]);
		else
			*val = lm90_get_temp11(data,
					       lm90_temp_max_index[channel]);
		break;
	case hwmon_temp_crit:
		*val = lm90_get_temp8(data, lm90_temp_crit_index[channel]);
		break;
	case hwmon_temp_crit_hyst:
		*val = lm90_get_temphyst(data, lm90_temp_crit_index[channel]);
		break;
	case hwmon_temp_emergency:
		*val = lm90_get_temp8(data, lm90_temp_emerg_index[channel]);
		break;
	case hwmon_temp_emergency_hyst:
		*val = lm90_get_temphyst(data, lm90_temp_emerg_index[channel]);
		break;
	case hwmon_temp_offset:
		*val = lm90_get_temp11(data, REMOTE_OFFSET);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}