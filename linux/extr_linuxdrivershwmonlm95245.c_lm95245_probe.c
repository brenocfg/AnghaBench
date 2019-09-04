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
struct lm95245_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct lm95245_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lm95245_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lm95245_chip_info ; 
 int lm95245_init_client (struct lm95245_data*) ; 
 int /*<<< orphan*/  lm95245_regmap_config ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm95245_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct lm95245_data *data;
	struct device *hwmon_dev;
	int ret;

	data = devm_kzalloc(dev, sizeof(struct lm95245_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->regmap = devm_regmap_init_i2c(client, &lm95245_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	mutex_init(&data->update_lock);

	/* Initialize the LM95245 chip */
	ret = lm95245_init_client(data);
	if (ret < 0)
		return ret;

	hwmon_dev = devm_hwmon_device_register_with_info(dev, client->name,
							 data,
							 &lm95245_chip_info,
							 NULL);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}