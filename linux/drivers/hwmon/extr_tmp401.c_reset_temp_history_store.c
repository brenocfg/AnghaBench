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
struct tmp401_data {int /*<<< orphan*/  update_lock; scalar_t__ valid; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/ ** TMP401_TEMP_MSB_WRITE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,long) ; 
 struct tmp401_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t reset_temp_history_store(struct device *dev,
					struct device_attribute *devattr,
					const char *buf, size_t count)
{
	struct tmp401_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;

	if (kstrtol(buf, 10, &val))
		return -EINVAL;

	if (val != 1) {
		dev_err(dev,
			"temp_reset_history value %ld not supported. Use 1 to reset the history!\n",
			val);
		return -EINVAL;
	}
	mutex_lock(&data->update_lock);
	i2c_smbus_write_byte_data(client, TMP401_TEMP_MSB_WRITE[5][0], val);
	data->valid = 0;
	mutex_unlock(&data->update_lock);

	return count;
}