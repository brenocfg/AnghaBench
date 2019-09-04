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
struct sht15_data {int measurements_valid; int /*<<< orphan*/  read_lock; scalar_t__ last_measurement; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SHT15_MEASURE_RH ; 
 int /*<<< orphan*/  SHT15_MEASURE_TEMP ; 
 int /*<<< orphan*/  SHT15_READING_HUMID ; 
 int /*<<< orphan*/  SHT15_READING_TEMP ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sht15_measurement (struct sht15_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sht15_update_measurements(struct sht15_data *data)
{
	int ret = 0;
	int timeout = HZ;

	mutex_lock(&data->read_lock);
	if (time_after(jiffies, data->last_measurement + timeout)
	    || !data->measurements_valid) {
		data->state = SHT15_READING_HUMID;
		ret = sht15_measurement(data, SHT15_MEASURE_RH, 160);
		if (ret)
			goto unlock;
		data->state = SHT15_READING_TEMP;
		ret = sht15_measurement(data, SHT15_MEASURE_TEMP, 400);
		if (ret)
			goto unlock;
		data->measurements_valid = true;
		data->last_measurement = jiffies;
	}

unlock:
	mutex_unlock(&data->read_lock);
	return ret;
}