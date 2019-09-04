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
struct sht3x_data {int /*<<< orphan*/  i2c_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHT3X_CMD_LENGTH ; 
 struct sht3x_data* dev_get_drvdata (struct device*) ; 
 int i2c_master_send (struct i2c_client*,char*,int /*<<< orphan*/ ) ; 
 int kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sht3x_cmd_heater_off ; 
 int /*<<< orphan*/  sht3x_cmd_heater_on ; 

__attribute__((used)) static ssize_t heater_enable_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf,
				   size_t count)
{
	struct sht3x_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret;
	bool status;

	ret = kstrtobool(buf, &status);
	if (ret)
		return ret;

	mutex_lock(&data->i2c_lock);

	if (status)
		ret = i2c_master_send(client, (char *)&sht3x_cmd_heater_on,
				      SHT3X_CMD_LENGTH);
	else
		ret = i2c_master_send(client, (char *)&sht3x_cmd_heater_off,
				      SHT3X_CMD_LENGTH);

	mutex_unlock(&data->i2c_lock);

	return ret;
}