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
struct lm3697 {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * dev; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
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
 struct lm3697* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3697*) ; 
 int /*<<< orphan*/  leds ; 
 int lm3697_init (struct lm3697*) ; 
 int lm3697_probe_dt (struct lm3697*) ; 
 int /*<<< orphan*/  lm3697_regmap_config ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct lm3697*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm3697_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct lm3697 *led;
	int count;
	int ret;

	count = device_get_child_node_count(&client->dev);
	if (!count) {
		dev_err(&client->dev, "LEDs are not defined in device tree!");
		return -ENODEV;
	}

	led = devm_kzalloc(&client->dev, struct_size(led, leds, count),
			   GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	mutex_init(&led->lock);
	i2c_set_clientdata(client, led);

	led->client = client;
	led->dev = &client->dev;
	led->regmap = devm_regmap_init_i2c(client, &lm3697_regmap_config);
	if (IS_ERR(led->regmap)) {
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = lm3697_probe_dt(led);
	if (ret)
		return ret;

	return lm3697_init(led);
}