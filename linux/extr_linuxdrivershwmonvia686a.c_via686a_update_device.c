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
struct via686a_data {int valid; int* in; int* in_min; int* in_max; int* fan; int* fan_min; int* temp; int* temp_over; int* temp_hyst; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  VIA686A_REG_ALARM1 ; 
 int /*<<< orphan*/  VIA686A_REG_ALARM2 ; 
 int /*<<< orphan*/  VIA686A_REG_FAN (int) ; 
 int /*<<< orphan*/  VIA686A_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  VIA686A_REG_IN (int) ; 
 int /*<<< orphan*/  VIA686A_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  VIA686A_REG_IN_MIN (int) ; 
 int /*<<< orphan*/ * VIA686A_REG_TEMP ; 
 int /*<<< orphan*/ * VIA686A_REG_TEMP_HYST ; 
 int /*<<< orphan*/  VIA686A_REG_TEMP_LOW1 ; 
 int /*<<< orphan*/  VIA686A_REG_TEMP_LOW23 ; 
 int /*<<< orphan*/ * VIA686A_REG_TEMP_OVER ; 
 struct via686a_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int via686a_read_value (struct via686a_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via686a_update_fan_div (struct via686a_data*) ; 

__attribute__((used)) static struct via686a_data *via686a_update_device(struct device *dev)
{
	struct via686a_data *data = dev_get_drvdata(dev);
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		for (i = 0; i <= 4; i++) {
			data->in[i] =
			    via686a_read_value(data, VIA686A_REG_IN(i));
			data->in_min[i] = via686a_read_value(data,
							     VIA686A_REG_IN_MIN
							     (i));
			data->in_max[i] =
			    via686a_read_value(data, VIA686A_REG_IN_MAX(i));
		}
		for (i = 1; i <= 2; i++) {
			data->fan[i - 1] =
			    via686a_read_value(data, VIA686A_REG_FAN(i));
			data->fan_min[i - 1] = via686a_read_value(data,
						     VIA686A_REG_FAN_MIN(i));
		}
		for (i = 0; i <= 2; i++) {
			data->temp[i] = via686a_read_value(data,
						 VIA686A_REG_TEMP[i]) << 2;
			data->temp_over[i] =
			    via686a_read_value(data,
					       VIA686A_REG_TEMP_OVER[i]);
			data->temp_hyst[i] =
			    via686a_read_value(data,
					       VIA686A_REG_TEMP_HYST[i]);
		}
		/*
		 * add in lower 2 bits
		 * temp1 uses bits 7-6 of VIA686A_REG_TEMP_LOW1
		 * temp2 uses bits 5-4 of VIA686A_REG_TEMP_LOW23
		 * temp3 uses bits 7-6 of VIA686A_REG_TEMP_LOW23
		 */
		data->temp[0] |= (via686a_read_value(data,
						     VIA686A_REG_TEMP_LOW1)
				  & 0xc0) >> 6;
		data->temp[1] |=
		    (via686a_read_value(data, VIA686A_REG_TEMP_LOW23) &
		     0x30) >> 4;
		data->temp[2] |=
		    (via686a_read_value(data, VIA686A_REG_TEMP_LOW23) &
		     0xc0) >> 6;

		via686a_update_fan_div(data);
		data->alarms =
		    via686a_read_value(data,
				       VIA686A_REG_ALARM1) |
		    (via686a_read_value(data, VIA686A_REG_ALARM2) << 8);
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}