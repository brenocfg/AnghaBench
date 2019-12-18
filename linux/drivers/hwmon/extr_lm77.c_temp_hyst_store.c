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
struct lm77_data {long* temp; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM77_REG_TEMP_HYST ; 
 int /*<<< orphan*/  LM77_TEMP_MAX ; 
 int /*<<< orphan*/  LM77_TEMP_MIN ; 
 int /*<<< orphan*/  LM77_TEMP_TO_REG (long) ; 
 long clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lm77_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  lm77_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t t_crit ; 
 size_t t_hyst ; 

__attribute__((used)) static ssize_t temp_hyst_store(struct device *dev,
			       struct device_attribute *devattr,
			       const char *buf, size_t count)
{
	struct lm77_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	val = clamp_val(data->temp[t_crit] - val, LM77_TEMP_MIN, LM77_TEMP_MAX);
	data->temp[t_hyst] = val;
	lm77_write_value(client, LM77_REG_TEMP_HYST,
			 LM77_TEMP_TO_REG(data->temp[t_hyst]));
	mutex_unlock(&data->update_lock);
	return count;
}