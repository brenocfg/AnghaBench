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
typedef  int u32 ;
struct lm90_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct lm90_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_chip_update_interval 128 
 int lm90_set_convrate (struct i2c_client*,struct lm90_data*,int /*<<< orphan*/ ) ; 
 int lm90_update_device (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm90_chip_write(struct device *dev, u32 attr, int channel, long val)
{
	struct lm90_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int err;

	mutex_lock(&data->update_lock);

	err = lm90_update_device(dev);
	if (err)
		goto error;

	switch (attr) {
	case hwmon_chip_update_interval:
		err = lm90_set_convrate(client, data,
					clamp_val(val, 0, 100000));
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}
error:
	mutex_unlock(&data->update_lock);

	return err;
}