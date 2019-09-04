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
struct abituguru3_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/ * settings; int /*<<< orphan*/ * value; int /*<<< orphan*/  alarms; } ;

/* Variables and functions */
 scalar_t__ ABIT_UGURU3_ALARMS_START ; 
 int /*<<< orphan*/  ABIT_UGURU3_SENSORS_BANK ; 
 int /*<<< orphan*/  ABIT_UGURU3_SETTINGS_BANK ; 
 scalar_t__ ABIT_UGURU3_SETTINGS_START ; 
 scalar_t__ ABIT_UGURU3_VALUES_START ; 
 scalar_t__ HZ ; 
 int abituguru3_read (struct abituguru3_data*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int abituguru3_read_increment_offset (struct abituguru3_data*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 struct abituguru3_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct abituguru3_data *abituguru3_update_device(struct device *dev)
{
	int i;
	struct abituguru3_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);
	if (!data->valid || time_after(jiffies, data->last_updated + HZ)) {
		/* Clear data->valid while updating */
		data->valid = 0;
		/* Read alarms */
		if (abituguru3_read_increment_offset(data,
				ABIT_UGURU3_SETTINGS_BANK,
				ABIT_UGURU3_ALARMS_START,
				1, data->alarms, 48/8) != (48/8))
			goto LEAVE_UPDATE;
		/* Read in and temp sensors (3 byte settings / sensor) */
		for (i = 0; i < 32; i++) {
			if (abituguru3_read(data, ABIT_UGURU3_SENSORS_BANK,
					ABIT_UGURU3_VALUES_START + i,
					1, &data->value[i]) != 1)
				goto LEAVE_UPDATE;
			if (abituguru3_read_increment_offset(data,
					ABIT_UGURU3_SETTINGS_BANK,
					ABIT_UGURU3_SETTINGS_START + i * 3,
					1,
					data->settings[i], 3) != 3)
				goto LEAVE_UPDATE;
		}
		/* Read temp sensors (2 byte settings / sensor) */
		for (i = 0; i < 16; i++) {
			if (abituguru3_read(data, ABIT_UGURU3_SENSORS_BANK,
					ABIT_UGURU3_VALUES_START + 32 + i,
					1, &data->value[32 + i]) != 1)
				goto LEAVE_UPDATE;
			if (abituguru3_read_increment_offset(data,
					ABIT_UGURU3_SETTINGS_BANK,
					ABIT_UGURU3_SETTINGS_START + 32 * 3 +
						i * 2, 1,
					data->settings[32 + i], 2) != 2)
				goto LEAVE_UPDATE;
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}
LEAVE_UPDATE:
	mutex_unlock(&data->update_lock);
	if (data->valid)
		return data;
	else
		return NULL;
}