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
struct sis5595_data {int valid; int maxins; int* in; int* in_min; int* in_max; int* fan; int* fan_min; int temp; int temp_over; int temp_hyst; int* fan_div; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SIS5595_REG_ALARM1 ; 
 int /*<<< orphan*/  SIS5595_REG_ALARM2 ; 
 int /*<<< orphan*/  SIS5595_REG_FAN (int) ; 
 int /*<<< orphan*/  SIS5595_REG_FANDIV ; 
 int /*<<< orphan*/  SIS5595_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  SIS5595_REG_IN (int) ; 
 int /*<<< orphan*/  SIS5595_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  SIS5595_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  SIS5595_REG_TEMP ; 
 int /*<<< orphan*/  SIS5595_REG_TEMP_HYST ; 
 int /*<<< orphan*/  SIS5595_REG_TEMP_OVER ; 
 struct sis5595_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sis5595_read_value (struct sis5595_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct sis5595_data *sis5595_update_device(struct device *dev)
{
	struct sis5595_data *data = dev_get_drvdata(dev);
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {

		for (i = 0; i <= data->maxins; i++) {
			data->in[i] =
			    sis5595_read_value(data, SIS5595_REG_IN(i));
			data->in_min[i] =
			    sis5595_read_value(data,
					       SIS5595_REG_IN_MIN(i));
			data->in_max[i] =
			    sis5595_read_value(data,
					       SIS5595_REG_IN_MAX(i));
		}
		for (i = 0; i < 2; i++) {
			data->fan[i] =
			    sis5595_read_value(data, SIS5595_REG_FAN(i));
			data->fan_min[i] =
			    sis5595_read_value(data,
					       SIS5595_REG_FAN_MIN(i));
		}
		if (data->maxins == 3) {
			data->temp =
			    sis5595_read_value(data, SIS5595_REG_TEMP);
			data->temp_over =
			    sis5595_read_value(data, SIS5595_REG_TEMP_OVER);
			data->temp_hyst =
			    sis5595_read_value(data, SIS5595_REG_TEMP_HYST);
		}
		i = sis5595_read_value(data, SIS5595_REG_FANDIV);
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = i >> 6;
		data->alarms =
		    sis5595_read_value(data, SIS5595_REG_ALARM1) |
		    (sis5595_read_value(data, SIS5595_REG_ALARM2) << 8);
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}