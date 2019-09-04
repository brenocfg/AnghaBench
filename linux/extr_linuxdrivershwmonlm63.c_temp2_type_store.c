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
typedef  int u8 ;
struct lm63_data {int trutherm; int /*<<< orphan*/  update_lock; scalar_t__ valid; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LM96163_REG_TRUTHERM ; 
 struct lm63_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t temp2_type_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct lm63_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long val;
	int ret;
	u8 reg;

	ret = kstrtoul(buf, 10, &val);
	if (ret < 0)
		return ret;
	if (val != 1 && val != 2)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->trutherm = val == 1;
	reg = i2c_smbus_read_byte_data(client, LM96163_REG_TRUTHERM) & ~0x02;
	i2c_smbus_write_byte_data(client, LM96163_REG_TRUTHERM,
				  reg | (data->trutherm ? 0x02 : 0x00));
	data->valid = 0;
	mutex_unlock(&data->update_lock);

	return count;
}