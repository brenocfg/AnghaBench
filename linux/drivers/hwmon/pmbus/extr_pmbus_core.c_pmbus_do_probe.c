#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pmbus_platform_data {int /*<<< orphan*/  flags; } ;
struct pmbus_driver_info {scalar_t__* groups; } ;
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;
struct pmbus_data {TYPE_1__ group; int /*<<< orphan*/  hwmon_dev; TYPE_1__** groups; int /*<<< orphan*/  num_attributes; struct pmbus_driver_info* info; int /*<<< orphan*/  flags; struct device* dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pmbus_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 TYPE_1__** devm_kcalloc (struct device*,size_t,int,int /*<<< orphan*/ ) ; 
 struct pmbus_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct pmbus_data*,TYPE_1__**) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pmbus_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,scalar_t__*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pmbus_find_attributes (struct i2c_client*,struct pmbus_data*) ; 
 int pmbus_init_common (struct i2c_client*,struct pmbus_data*,struct pmbus_driver_info*) ; 
 int pmbus_init_debugfs (struct i2c_client*,struct pmbus_data*) ; 
 int pmbus_regulator_register (struct pmbus_data*) ; 

int pmbus_do_probe(struct i2c_client *client, const struct i2c_device_id *id,
		   struct pmbus_driver_info *info)
{
	struct device *dev = &client->dev;
	const struct pmbus_platform_data *pdata = dev_get_platdata(dev);
	struct pmbus_data *data;
	size_t groups_num = 0;
	int ret;

	if (!info)
		return -ENODEV;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WRITE_BYTE
				     | I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	if (info->groups)
		while (info->groups[groups_num])
			groups_num++;

	data->groups = devm_kcalloc(dev, groups_num + 2, sizeof(void *),
				    GFP_KERNEL);
	if (!data->groups)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->dev = dev;

	if (pdata)
		data->flags = pdata->flags;
	data->info = info;

	ret = pmbus_init_common(client, data, info);
	if (ret < 0)
		return ret;

	ret = pmbus_find_attributes(client, data);
	if (ret)
		goto out_kfree;

	/*
	 * If there are no attributes, something is wrong.
	 * Bail out instead of trying to register nothing.
	 */
	if (!data->num_attributes) {
		dev_err(dev, "No attributes found\n");
		ret = -ENODEV;
		goto out_kfree;
	}

	data->groups[0] = &data->group;
	memcpy(data->groups + 1, info->groups, sizeof(void *) * groups_num);
	data->hwmon_dev = hwmon_device_register_with_groups(dev, client->name,
							    data, data->groups);
	if (IS_ERR(data->hwmon_dev)) {
		ret = PTR_ERR(data->hwmon_dev);
		dev_err(dev, "Failed to register hwmon device\n");
		goto out_kfree;
	}

	ret = pmbus_regulator_register(data);
	if (ret)
		goto out_unregister;

	ret = pmbus_init_debugfs(client, data);
	if (ret)
		dev_warn(dev, "Failed to register debugfs\n");

	return 0;

out_unregister:
	hwmon_device_unregister(data->hwmon_dev);
out_kfree:
	kfree(data->group.attrs);
	return ret;
}