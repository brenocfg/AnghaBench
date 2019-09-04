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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct emc2103_data {int temp_count; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  REG_CONF1 ; 
 int /*<<< orphan*/  REG_PRODUCT_ID ; 
 int apd ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct emc2103_data*,int /*<<< orphan*/ **) ; 
 struct emc2103_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emc2103_group ; 
 int /*<<< orphan*/  emc2103_temp3_group ; 
 int /*<<< orphan*/  emc2103_temp4_group ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct emc2103_data*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
emc2103_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct emc2103_data *data;
	struct device *hwmon_dev;
	int status, idx = 0;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	data = devm_kzalloc(&client->dev, sizeof(struct emc2103_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* 2103-2 and 2103-4 have 3 external diodes, 2103-1 has 1 */
	status = i2c_smbus_read_byte_data(client, REG_PRODUCT_ID);
	if (status == 0x24) {
		/* 2103-1 only has 1 external diode */
		data->temp_count = 2;
	} else {
		/* 2103-2 and 2103-4 have 3 or 4 external diodes */
		status = i2c_smbus_read_byte_data(client, REG_CONF1);
		if (status < 0) {
			dev_dbg(&client->dev, "reg 0x%02x, err %d\n", REG_CONF1,
				status);
			return status;
		}

		/* detect current state of hardware */
		data->temp_count = (status & 0x01) ? 4 : 3;

		/* force APD state if module parameter is set */
		if (apd == 0) {
			/* force APD mode off */
			data->temp_count = 3;
			status &= ~(0x01);
			i2c_smbus_write_byte_data(client, REG_CONF1, status);
		} else if (apd == 1) {
			/* force APD mode on */
			data->temp_count = 4;
			status |= 0x01;
			i2c_smbus_write_byte_data(client, REG_CONF1, status);
		}
	}

	/* sysfs hooks */
	data->groups[idx++] = &emc2103_group;
	if (data->temp_count >= 3)
		data->groups[idx++] = &emc2103_temp3_group;
	if (data->temp_count == 4)
		data->groups[idx++] = &emc2103_temp4_group;

	hwmon_dev = devm_hwmon_device_register_with_groups(&client->dev,
							   client->name, data,
							   data->groups);
	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	dev_info(&client->dev, "%s: sensor '%s'\n",
		 dev_name(hwmon_dev), client->name);

	return 0;
}