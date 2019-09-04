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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct lt3593_led_data {TYPE_1__ cdev; int /*<<< orphan*/  gpiod; } ;
struct gpio_led_platform_data {int num_leds; struct gpio_led* leds; } ;
struct gpio_led {scalar_t__ default_state; int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; int /*<<< orphan*/  retain_state_suspended; int /*<<< orphan*/  default_trigger; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct lt3593_led_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 scalar_t__ LEDS_GPIO_DEFSTATE_ON ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 struct gpio_led_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lt3593_led_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lt3593_led_set ; 

__attribute__((used)) static struct lt3593_led_data *lt3593_led_probe_pdata(struct device *dev)
{
	struct gpio_led_platform_data *pdata = dev_get_platdata(dev);
	const struct gpio_led *template = &pdata->leds[0];
	struct lt3593_led_data *led_data;
	int ret, state;

	if (pdata->num_leds != 1)
		return ERR_PTR(-EINVAL);

	led_data = devm_kzalloc(dev, sizeof(*led_data), GFP_KERNEL);
	if (!led_data)
		return ERR_PTR(-ENOMEM);

	led_data->cdev.name = template->name;
	led_data->cdev.default_trigger = template->default_trigger;
	led_data->cdev.brightness_set_blocking = lt3593_led_set;

	state = (template->default_state == LEDS_GPIO_DEFSTATE_ON);
	led_data->cdev.brightness = state ? LED_FULL : LED_OFF;

	if (!template->retain_state_suspended)
		led_data->cdev.flags |= LED_CORE_SUSPENDRESUME;

	ret = devm_gpio_request_one(dev, template->gpio, state ?
				    GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW,
				    template->name);
	if (ret < 0)
		return ERR_PTR(ret);

	led_data->gpiod = gpio_to_desc(template->gpio);
	if (!led_data->gpiod)
		return ERR_PTR(-EPROBE_DEFER);

	ret = devm_led_classdev_register(dev, &led_data->cdev);
	if (ret < 0)
		return ERR_PTR(ret);

	dev_info(dev, "registered LT3593 LED '%s' at GPIO %d\n",
		 template->name, template->gpio);

	return led_data;
}