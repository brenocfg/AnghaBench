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
struct device {int dummy; } ;
struct abituguru_data {int bank2_sensors; unsigned int update_timeouts; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/ * bank2_value; int /*<<< orphan*/ ** bank1_settings; int /*<<< orphan*/ * bank1_value; int /*<<< orphan*/ * alarms; } ;

/* Variables and functions */
 scalar_t__ ABIT_UGURU_ALARM_BANK ; 
 int /*<<< orphan*/  ABIT_UGURU_DEBUG (int,char*,...) ; 
 int ABIT_UGURU_MAX_BANK1_SENSORS ; 
 unsigned int ABIT_UGURU_MAX_TIMEOUTS ; 
 scalar_t__ ABIT_UGURU_SENSOR_BANK1 ; 
 scalar_t__ ABIT_UGURU_SENSOR_BANK2 ; 
 int EBUSY ; 
 scalar_t__ HZ ; 
 int abituguru_read (struct abituguru_data*,scalar_t__,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct abituguru_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct abituguru_data *abituguru_update_device(struct device *dev)
{
	int i, err;
	struct abituguru_data *data = dev_get_drvdata(dev);
	/* fake a complete successful read if no update necessary. */
	char success = 1;

	mutex_lock(&data->update_lock);
	if (time_after(jiffies, data->last_updated + HZ)) {
		success = 0;
		err = abituguru_read(data, ABIT_UGURU_ALARM_BANK, 0,
				     data->alarms, 3, 0);
		if (err != 3)
			goto LEAVE_UPDATE;
		for (i = 0; i < ABIT_UGURU_MAX_BANK1_SENSORS; i++) {
			err = abituguru_read(data, ABIT_UGURU_SENSOR_BANK1,
					     i, &data->bank1_value[i], 1, 0);
			if (err != 1)
				goto LEAVE_UPDATE;
			err = abituguru_read(data, ABIT_UGURU_SENSOR_BANK1 + 1,
					     i, data->bank1_settings[i], 3, 0);
			if (err != 3)
				goto LEAVE_UPDATE;
		}
		for (i = 0; i < data->bank2_sensors; i++) {
			err = abituguru_read(data, ABIT_UGURU_SENSOR_BANK2, i,
					     &data->bank2_value[i], 1, 0);
			if (err != 1)
				goto LEAVE_UPDATE;
		}
		/* success! */
		success = 1;
		data->update_timeouts = 0;
LEAVE_UPDATE:
		/* handle timeout condition */
		if (!success && (err == -EBUSY || err >= 0)) {
			/* No overflow please */
			if (data->update_timeouts < 255u)
				data->update_timeouts++;
			if (data->update_timeouts <= ABIT_UGURU_MAX_TIMEOUTS) {
				ABIT_UGURU_DEBUG(3, "timeout exceeded, will "
					"try again next update\n");
				/* Just a timeout, fake a successful read */
				success = 1;
			} else
				ABIT_UGURU_DEBUG(1, "timeout exceeded %d "
					"times waiting for more input state\n",
					(int)data->update_timeouts);
		}
		/* On success set last_updated */
		if (success)
			data->last_updated = jiffies;
	}
	mutex_unlock(&data->update_lock);

	if (success)
		return data;
	else
		return NULL;
}