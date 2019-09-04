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
typedef  int /*<<< orphan*/  u16 ;
struct sht3x_data {size_t mode; int /*<<< orphan*/  data_lock; scalar_t__ last_update; int /*<<< orphan*/  humidity; int /*<<< orphan*/  temperature; int /*<<< orphan*/  wait_time; int /*<<< orphan*/  command; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct sht3x_data* ERR_PTR (int) ; 
 int SHT3X_RESPONSE_LENGTH ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 struct sht3x_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * mode_to_update_interval ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sht3x_extract_humidity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sht3x_extract_temperature (int /*<<< orphan*/ ) ; 
 int sht3x_read_from_command (struct i2c_client*,struct sht3x_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct sht3x_data *sht3x_update_client(struct device *dev)
{
	struct sht3x_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u16 interval_ms = mode_to_update_interval[data->mode];
	unsigned long interval_jiffies = msecs_to_jiffies(interval_ms);
	unsigned char buf[SHT3X_RESPONSE_LENGTH];
	u16 val;
	int ret = 0;

	mutex_lock(&data->data_lock);
	/*
	 * Only update cached readings once per update interval in periodic
	 * mode. In single shot mode the sensor measures values on demand, so
	 * every time the sysfs interface is called, a measurement is triggered.
	 * In periodic mode however, the measurement process is handled
	 * internally by the sensor and reading out sensor values only makes
	 * sense if a new reading is available.
	 */
	if (time_after(jiffies, data->last_update + interval_jiffies)) {
		ret = sht3x_read_from_command(client, data, data->command, buf,
					      sizeof(buf), data->wait_time);
		if (ret)
			goto out;

		val = be16_to_cpup((__be16 *)buf);
		data->temperature = sht3x_extract_temperature(val);
		val = be16_to_cpup((__be16 *)(buf + 3));
		data->humidity = sht3x_extract_humidity(val);
		data->last_update = jiffies;
	}

out:
	mutex_unlock(&data->data_lock);
	if (ret)
		return ERR_PTR(ret);

	return data;
}