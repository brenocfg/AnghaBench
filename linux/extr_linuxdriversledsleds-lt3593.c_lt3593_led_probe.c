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
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {char const* default_trigger; TYPE_1__* dev; int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  name; } ;
struct lt3593_led_data {TYPE_2__ cdev; int /*<<< orphan*/  name; struct lt3593_led_data* gpiod; } ;
struct fwnode_handle {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;
struct TYPE_3__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_ASIS ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct lt3593_led_data*) ; 
 int LEDS_GPIO_DEFSTATE_KEEP ; 
 int LEDS_GPIO_DEFSTATE_OFF ; 
 int LEDS_GPIO_DEFSTATE_ON ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int PTR_ERR (struct lt3593_led_data*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dev_get_platdata (struct device*) ; 
 int device_get_child_node_count (struct device*) ; 
 struct fwnode_handle* device_get_next_child_node (struct device*,int /*<<< orphan*/ *) ; 
 struct lt3593_led_data* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct lt3593_led_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (struct device*,TYPE_2__*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int fwnode_property_read_string (struct fwnode_handle*,char*,char const**) ; 
 struct lt3593_led_data* lt3593_led_probe_pdata (struct device*) ; 
 int /*<<< orphan*/  lt3593_led_set ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lt3593_led_data*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int lt3593_led_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct lt3593_led_data *led_data;
	struct fwnode_handle *child;
	int ret, state = LEDS_GPIO_DEFSTATE_OFF;
	enum gpiod_flags flags = GPIOD_OUT_LOW;
	const char *tmp;

	if (dev_get_platdata(dev)) {
		led_data = lt3593_led_probe_pdata(dev);
		if (IS_ERR(led_data))
			return PTR_ERR(led_data);

		goto out;
	}

	if (!dev->of_node)
		return -ENODEV;

	led_data = devm_kzalloc(dev, sizeof(*led_data), GFP_KERNEL);
	if (!led_data)
		return -ENOMEM;

	if (device_get_child_node_count(dev) != 1) {
		dev_err(dev, "Device must have exactly one LED sub-node.");
		return -EINVAL;
	}

	led_data->gpiod = devm_gpiod_get(dev, "lltc,ctrl", 0);
	if (IS_ERR(led_data->gpiod))
		return PTR_ERR(led_data->gpiod);

	child = device_get_next_child_node(dev, NULL);

	ret = fwnode_property_read_string(child, "label", &tmp);
	if (ret < 0)
		snprintf(led_data->name, sizeof(led_data->name),
			 "lt3593::");
	else
		snprintf(led_data->name, sizeof(led_data->name),
			 "lt3593:%s", tmp);

	fwnode_property_read_string(child, "linux,default-trigger",
				    &led_data->cdev.default_trigger);

	if (!fwnode_property_read_string(child, "default-state", &tmp)) {
		if (!strcmp(tmp, "keep")) {
			state = LEDS_GPIO_DEFSTATE_KEEP;
			flags = GPIOD_ASIS;
		} else if (!strcmp(tmp, "on")) {
			state = LEDS_GPIO_DEFSTATE_ON;
			flags = GPIOD_OUT_HIGH;
		}
	}

	led_data->cdev.name = led_data->name;
	led_data->cdev.brightness_set_blocking = lt3593_led_set;
	led_data->cdev.brightness = state ? LED_FULL : LED_OFF;

	ret = devm_led_classdev_register(dev, &led_data->cdev);
	if (ret < 0) {
		fwnode_handle_put(child);
		return ret;
	}

	led_data->cdev.dev->of_node = dev->of_node;

out:
	platform_set_drvdata(pdev, led_data);

	return 0;
}