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
struct lm3532_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * dev; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int device_get_child_node_count (int /*<<< orphan*/ *) ; 
 struct lm3532_data* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3532_data*) ; 
 int /*<<< orphan*/  leds ; 
 int lm3532_parse_node (struct lm3532_data*) ; 
 int /*<<< orphan*/  lm3532_regmap_config ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct lm3532_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm3532_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct lm3532_data *drvdata;
	int ret = 0;
	int count;

	count = device_get_child_node_count(&client->dev);
	if (!count) {
		dev_err(&client->dev, "LEDs are not defined in device tree!");
		return -ENODEV;
	}

	drvdata = devm_kzalloc(&client->dev, struct_size(drvdata, leds, count),
			   GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	drvdata->client = client;
	drvdata->dev = &client->dev;

	drvdata->regmap = devm_regmap_init_i2c(client, &lm3532_regmap_config);
	if (IS_ERR(drvdata->regmap)) {
		ret = PTR_ERR(drvdata->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	mutex_init(&drvdata->lock);
	i2c_set_clientdata(client, drvdata);

	ret = lm3532_parse_node(drvdata);
	if (ret) {
		dev_err(&client->dev, "Failed to parse node\n");
		return ret;
	}

	return ret;
}