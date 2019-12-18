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
struct sy8824_device_info {scalar_t__ regulator; struct device* dev; int /*<<< orphan*/  cfg; int /*<<< orphan*/  desc; } ;
struct regulator_config {struct device_node* of_node; struct sy8824_device_info* driver_data; struct regmap* regmap; scalar_t__ init_data; struct device* dev; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct i2c_client {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sy8824_device_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sy8824_device_info*) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 scalar_t__ of_get_regulator_init_data (struct device*,struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sy8824_regmap_config ; 
 int sy8824_regulator_register (struct sy8824_device_info*,struct regulator_config*) ; 

__attribute__((used)) static int sy8824_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device_node *np = dev->of_node;
	struct sy8824_device_info *di;
	struct regulator_config config = { };
	struct regmap *regmap;
	int ret;

	di = devm_kzalloc(dev, sizeof(struct sy8824_device_info), GFP_KERNEL);
	if (!di)
		return -ENOMEM;

	di->regulator = of_get_regulator_init_data(dev, np, &di->desc);
	if (!di->regulator) {
		dev_err(dev, "Platform data not found!\n");
		return -EINVAL;
	}

	di->dev = dev;
	di->cfg = of_device_get_match_data(dev);

	regmap = devm_regmap_init_i2c(client, &sy8824_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(dev, "Failed to allocate regmap!\n");
		return PTR_ERR(regmap);
	}
	i2c_set_clientdata(client, di);

	config.dev = di->dev;
	config.init_data = di->regulator;
	config.regmap = regmap;
	config.driver_data = di;
	config.of_node = np;

	ret = sy8824_regulator_register(di, &config);
	if (ret < 0)
		dev_err(dev, "Failed to register regulator!\n");
	return ret;
}