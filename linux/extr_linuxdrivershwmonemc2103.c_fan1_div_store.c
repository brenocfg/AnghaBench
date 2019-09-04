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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct emc2103_data {int fan_multiplier; int fan_target; int valid; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_FAN_CONF1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct emc2103_data* emc2103_update_device (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_fan_target_to_i2c (struct i2c_client*,int) ; 

__attribute__((used)) static ssize_t fan1_div_store(struct device *dev, struct device_attribute *da,
			      const char *buf, size_t count)
{
	struct emc2103_data *data = emc2103_update_device(dev);
	struct i2c_client *client = data->client;
	int new_range_bits, old_div = 8 / data->fan_multiplier;
	long new_div;

	int status = kstrtol(buf, 10, &new_div);
	if (status < 0)
		return status;

	if (new_div == old_div) /* No change */
		return count;

	switch (new_div) {
	case 1:
		new_range_bits = 3;
		break;
	case 2:
		new_range_bits = 2;
		break;
	case 4:
		new_range_bits = 1;
		break;
	case 8:
		new_range_bits = 0;
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);

	status = i2c_smbus_read_byte_data(client, REG_FAN_CONF1);
	if (status < 0) {
		dev_dbg(&client->dev, "reg 0x%02x, err %d\n",
			REG_FAN_CONF1, status);
		mutex_unlock(&data->update_lock);
		return status;
	}
	status &= 0x9F;
	status |= (new_range_bits << 5);
	i2c_smbus_write_byte_data(client, REG_FAN_CONF1, status);

	data->fan_multiplier = 8 / new_div;

	/* update fan target if high byte is not disabled */
	if ((data->fan_target & 0x1fe0) != 0x1fe0) {
		u16 new_target = (data->fan_target * old_div) / new_div;
		data->fan_target = min(new_target, (u16)0x1fff);
		write_fan_target_to_i2c(client, data->fan_target);
	}

	/* invalidate data to force re-read from hardware */
	data->valid = false;

	mutex_unlock(&data->update_lock);
	return count;
}