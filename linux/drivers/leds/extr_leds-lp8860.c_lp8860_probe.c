#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  default_trigger; } ;
struct lp8860_led {TYPE_3__ led_dev; int /*<<< orphan*/ * eeprom_regmap; int /*<<< orphan*/ * regmap; int /*<<< orphan*/  lock; struct i2c_client* client; int /*<<< orphan*/ * regulator; int /*<<< orphan*/ * enable_gpio; } ;
struct led_init_data {char* default_label; int /*<<< orphan*/  devicename; int /*<<< orphan*/  fwnode; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LP8860_NAME ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct lp8860_led* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register_ext (TYPE_1__*,TYPE_3__*,struct led_init_data*) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lp8860_led*) ; 
 int /*<<< orphan*/  lp8860_brightness_set ; 
 int /*<<< orphan*/  lp8860_eeprom_regmap_config ; 
 int lp8860_init (struct lp8860_led*) ; 
 int /*<<< orphan*/  lp8860_regmap_config ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_get_next_available_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8860_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct lp8860_led *led;
	struct device_node *np = client->dev.of_node;
	struct device_node *child_node;
	struct led_init_data init_data = {};

	led = devm_kzalloc(&client->dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	child_node = of_get_next_available_child(np, NULL);
	if (!child_node)
		return -EINVAL;

	led->led_dev.default_trigger = of_get_property(child_node,
					    "linux,default-trigger",
					    NULL);

	led->enable_gpio = devm_gpiod_get_optional(&client->dev,
						   "enable", GPIOD_OUT_LOW);
	if (IS_ERR(led->enable_gpio)) {
		ret = PTR_ERR(led->enable_gpio);
		dev_err(&client->dev, "Failed to get enable gpio: %d\n", ret);
		return ret;
	}

	led->regulator = devm_regulator_get(&client->dev, "vled");
	if (IS_ERR(led->regulator))
		led->regulator = NULL;

	led->client = client;
	led->led_dev.brightness_set_blocking = lp8860_brightness_set;

	mutex_init(&led->lock);

	i2c_set_clientdata(client, led);

	led->regmap = devm_regmap_init_i2c(client, &lp8860_regmap_config);
	if (IS_ERR(led->regmap)) {
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	led->eeprom_regmap = devm_regmap_init_i2c(client, &lp8860_eeprom_regmap_config);
	if (IS_ERR(led->eeprom_regmap)) {
		ret = PTR_ERR(led->eeprom_regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = lp8860_init(led);
	if (ret)
		return ret;

	init_data.fwnode = of_fwnode_handle(child_node);
	init_data.devicename = LP8860_NAME;
	init_data.default_label = ":display_cluster";

	ret = devm_led_classdev_register_ext(&client->dev, &led->led_dev,
					     &init_data);
	if (ret) {
		dev_err(&client->dev, "led register err: %d\n", ret);
		return ret;
	}

	return 0;
}