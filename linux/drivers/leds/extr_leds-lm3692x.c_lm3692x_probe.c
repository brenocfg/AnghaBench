#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  brightness_set_blocking; } ;
struct lm3692x_led {int /*<<< orphan*/  regmap; int /*<<< orphan*/  model_id; TYPE_1__ led_dev; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct lm3692x_led* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3692x_led*) ; 
 int /*<<< orphan*/  lm3692x_brightness_set ; 
 int lm3692x_init (struct lm3692x_led*) ; 
 int lm3692x_probe_dt (struct lm3692x_led*) ; 
 int /*<<< orphan*/  lm3692x_regmap_config ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3692x_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct lm3692x_led *led;
	int ret;

	led = devm_kzalloc(&client->dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	mutex_init(&led->lock);
	led->client = client;
	led->led_dev.brightness_set_blocking = lm3692x_brightness_set;
	led->model_id = id->driver_data;
	i2c_set_clientdata(client, led);

	led->regmap = devm_regmap_init_i2c(client, &lm3692x_regmap_config);
	if (IS_ERR(led->regmap)) {
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = lm3692x_probe_dt(led);
	if (ret)
		return ret;

	ret = lm3692x_init(led);
	if (ret)
		return ret;

	return 0;
}