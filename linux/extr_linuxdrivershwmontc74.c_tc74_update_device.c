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
struct tc74_data {int valid; int temp_input; int /*<<< orphan*/  lock; scalar_t__ next_update; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int EAGAIN ; 
 int HZ ; 
 int /*<<< orphan*/  TC74_REG_CONFIG ; 
 int /*<<< orphan*/  TC74_REG_TEMP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct tc74_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int tc74_update_device(struct device *dev)
{
	struct tc74_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret;

	ret = mutex_lock_interruptible(&data->lock);
	if (ret)
		return ret;

	if (time_after(jiffies, data->next_update) || !data->valid) {
		s32 value;

		value = i2c_smbus_read_byte_data(client, TC74_REG_CONFIG);
		if (value < 0) {
			dev_dbg(&client->dev, "TC74_REG_CONFIG read err %d\n",
				(int)value);

			ret = value;
			goto ret_unlock;
		}

		if (!(value & BIT(6))) {
			/* not ready yet */

			ret = -EAGAIN;
			goto ret_unlock;
		}

		value = i2c_smbus_read_byte_data(client, TC74_REG_TEMP);
		if (value < 0) {
			dev_dbg(&client->dev, "TC74_REG_TEMP read err %d\n",
				(int)value);

			ret = value;
			goto ret_unlock;
		}

		data->temp_input = value;
		data->next_update = jiffies + HZ / 4;
		data->valid = true;
	}

ret_unlock:
	mutex_unlock(&data->lock);

	return ret;
}