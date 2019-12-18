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
struct i2c_client {int dummy; } ;
struct g762_data {int valid; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  G762_REG_SET_OUT ; 
 struct g762_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_set_pwm(struct device *dev, unsigned long val)
{
	struct g762_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ret;

	if (val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client, G762_REG_SET_OUT, val);
	data->valid = false;
	mutex_unlock(&data->update_lock);

	return ret;
}