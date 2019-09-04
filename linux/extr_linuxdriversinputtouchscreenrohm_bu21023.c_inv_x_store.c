#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rohm_ts_data {TYPE_1__* input; int /*<<< orphan*/  setup2; int /*<<< orphan*/  client; scalar_t__ initialized; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_SETUP2 ; 
 int /*<<< orphan*/  INV_X ; 
 struct rohm_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t inv_x_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rohm_ts_data *ts = i2c_get_clientdata(client);
	unsigned int val;
	int error;

	error = kstrtouint(buf, 0, &val);
	if (error)
		return error;

	error = mutex_lock_interruptible(&ts->input->mutex);
	if (error)
		return error;

	if (val)
		ts->setup2 |= INV_X;
	else
		ts->setup2 &= ~INV_X;

	if (ts->initialized)
		error = i2c_smbus_write_byte_data(ts->client, COMMON_SETUP2,
						  ts->setup2);

	mutex_unlock(&ts->input->mutex);

	return error ? error : count;
}