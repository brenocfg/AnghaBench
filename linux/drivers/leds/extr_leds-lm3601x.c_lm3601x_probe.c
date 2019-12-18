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
struct lm3601x_led {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct lm3601x_led* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3601x_led*) ; 
 int lm3601x_parse_node (struct lm3601x_led*,struct fwnode_handle**) ; 
 int lm3601x_register_leds (struct lm3601x_led*,struct fwnode_handle*) ; 
 int /*<<< orphan*/  lm3601x_regmap ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3601x_probe(struct i2c_client *client)
{
	struct lm3601x_led *led;
	struct fwnode_handle *fwnode;
	int ret;

	led = devm_kzalloc(&client->dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->client = client;
	i2c_set_clientdata(client, led);

	ret = lm3601x_parse_node(led, &fwnode);
	if (ret)
		return -ENODEV;

	led->regmap = devm_regmap_init_i2c(client, &lm3601x_regmap);
	if (IS_ERR(led->regmap)) {
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map: %d\n", ret);
		return ret;
	}

	mutex_init(&led->lock);

	return lm3601x_register_leds(led, fwnode);
}