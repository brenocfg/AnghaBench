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
struct lm63_data {long temp2_offset; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  HYST_TO_REG (long) ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TCRIT_HYST ; 
 struct lm63_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long temp8_from_reg (struct lm63_data*,int) ; 

__attribute__((used)) static ssize_t temp2_crit_hyst_store(struct device *dev,
				     struct device_attribute *dummy,
				     const char *buf, size_t count)
{
	struct lm63_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;
	long hyst;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	hyst = temp8_from_reg(data, 2) + data->temp2_offset - val;
	i2c_smbus_write_byte_data(client, LM63_REG_REMOTE_TCRIT_HYST,
				  HYST_TO_REG(hyst));
	mutex_unlock(&data->update_lock);
	return count;
}