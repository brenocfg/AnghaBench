#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  default_trigger; } ;
struct lm3692x_led {TYPE_1__* client; TYPE_2__ led_dev; int /*<<< orphan*/  led_enable; int /*<<< orphan*/ * regulator; int /*<<< orphan*/ * enable_gpio; } ;
struct led_init_data {char* default_label; int /*<<< orphan*/  devicename; struct fwnode_handle* fwnode; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct fwnode_handle* device_get_next_child_node (int /*<<< orphan*/ *,struct fwnode_handle*) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register_ext (int /*<<< orphan*/ *,TYPE_2__*,struct led_init_data*) ; 
 int /*<<< orphan*/ * devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fwnode_property_read_string (struct fwnode_handle*,char*,int /*<<< orphan*/ *) ; 
 int fwnode_property_read_u32 (struct fwnode_handle*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3692x_probe_dt(struct lm3692x_led *led)
{
	struct fwnode_handle *child = NULL;
	struct led_init_data init_data = {};
	int ret;

	led->enable_gpio = devm_gpiod_get_optional(&led->client->dev,
						   "enable", GPIOD_OUT_LOW);
	if (IS_ERR(led->enable_gpio)) {
		ret = PTR_ERR(led->enable_gpio);
		dev_err(&led->client->dev, "Failed to get enable gpio: %d\n",
			ret);
		return ret;
	}

	led->regulator = devm_regulator_get(&led->client->dev, "vled");
	if (IS_ERR(led->regulator))
		led->regulator = NULL;

	child = device_get_next_child_node(&led->client->dev, child);
	if (!child) {
		dev_err(&led->client->dev, "No LED Child node\n");
		return -ENODEV;
	}

	fwnode_property_read_string(child, "linux,default-trigger",
				    &led->led_dev.default_trigger);

	ret = fwnode_property_read_u32(child, "reg", &led->led_enable);
	if (ret) {
		dev_err(&led->client->dev, "reg DT property missing\n");
		return ret;
	}

	init_data.fwnode = child;
	init_data.devicename = led->client->name;
	init_data.default_label = ":";

	ret = devm_led_classdev_register_ext(&led->client->dev, &led->led_dev,
					     &init_data);
	if (ret) {
		dev_err(&led->client->dev, "led register err: %d\n", ret);
		return ret;
	}

	return 0;
}