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
struct mip4_ts {int product_id; TYPE_1__* input; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct mip4_ts* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t mip4_sysfs_read_product_id(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mip4_ts *ts = i2c_get_clientdata(client);
	size_t count;

	mutex_lock(&ts->input->mutex);

	count = snprintf(buf, PAGE_SIZE, "%04X\n", ts->product_id);

	mutex_unlock(&ts->input->mutex);

	return count;
}