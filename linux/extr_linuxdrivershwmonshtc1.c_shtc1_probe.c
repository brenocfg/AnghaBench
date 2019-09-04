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
struct shtc1_platform_data {int blocking_io; int high_precision; } ;
struct shtc1_data {int /*<<< orphan*/  update_lock; struct shtc1_platform_data setup; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {scalar_t__ platform_data; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  id_reg ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int SHTC1_CMD_LENGTH ; 
 char SHTC1_ID ; 
 char SHTC1_ID_REG_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct shtc1_data*,int /*<<< orphan*/ ) ; 
 struct shtc1_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shtc1_cmd_read_id_reg ; 
 int /*<<< orphan*/  shtc1_groups ; 
 int /*<<< orphan*/  shtc1_select_command (struct shtc1_data*) ; 

__attribute__((used)) static int shtc1_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	int ret;
	char id_reg[2];
	struct shtc1_data *data;
	struct device *hwmon_dev;
	struct i2c_adapter *adap = client->adapter;
	struct device *dev = &client->dev;

	if (!i2c_check_functionality(adap, I2C_FUNC_I2C)) {
		dev_err(dev, "plain i2c transactions not supported\n");
		return -ENODEV;
	}

	ret = i2c_master_send(client, shtc1_cmd_read_id_reg, SHTC1_CMD_LENGTH);
	if (ret != SHTC1_CMD_LENGTH) {
		dev_err(dev, "could not send read_id_reg command: %d\n", ret);
		return ret < 0 ? ret : -ENODEV;
	}
	ret = i2c_master_recv(client, id_reg, sizeof(id_reg));
	if (ret != sizeof(id_reg)) {
		dev_err(dev, "could not read ID register: %d\n", ret);
		return -ENODEV;
	}
	if ((id_reg[1] & SHTC1_ID_REG_MASK) != SHTC1_ID) {
		dev_err(dev, "ID register doesn't match\n");
		return -ENODEV;
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->setup.blocking_io = false;
	data->setup.high_precision = true;
	data->client = client;

	if (client->dev.platform_data)
		data->setup = *(struct shtc1_platform_data *)dev->platform_data;
	shtc1_select_command(data);
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
							   client->name,
							   data,
							   shtc1_groups);
	if (IS_ERR(hwmon_dev))
		dev_dbg(dev, "unable to register hwmon device\n");

	return PTR_ERR_OR_ZERO(hwmon_dev);
}