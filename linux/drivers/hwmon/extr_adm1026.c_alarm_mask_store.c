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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1026_data {long alarm_mask; int gpio_mask; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_MASK1 ; 
 int /*<<< orphan*/  ADM1026_REG_MASK2 ; 
 int /*<<< orphan*/  ADM1026_REG_MASK3 ; 
 int /*<<< orphan*/  ADM1026_REG_MASK4 ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 
 struct adm1026_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t alarm_mask_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct adm1026_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long mask;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->alarm_mask = val & 0x7fffffff;
	mask = data->alarm_mask
		| (data->gpio_mask & 0x10000 ? 0x80000000 : 0);
	adm1026_write_value(client, ADM1026_REG_MASK1,
		mask & 0xff);
	mask >>= 8;
	adm1026_write_value(client, ADM1026_REG_MASK2,
		mask & 0xff);
	mask >>= 8;
	adm1026_write_value(client, ADM1026_REG_MASK3,
		mask & 0xff);
	mask >>= 8;
	adm1026_write_value(client, ADM1026_REG_MASK4,
		mask & 0xff);
	mutex_unlock(&data->update_lock);
	return count;
}