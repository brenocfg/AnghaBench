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
struct gpio_led {int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; scalar_t__ active_low; } ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct gpio_desc* ERR_PTR (int) ; 
 unsigned long GPIOF_ACTIVE_LOW ; 
 unsigned long GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct gpio_desc* gpio_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (struct gpio_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gpio_desc *gpio_led_get_gpiod(struct device *dev, int idx,
					    const struct gpio_led *template)
{
	struct gpio_desc *gpiod;
	unsigned long flags = GPIOF_OUT_INIT_LOW;
	int ret;

	/*
	 * This means the LED does not come from the device tree
	 * or ACPI, so let's try just getting it by index from the
	 * device, this will hit the board file, if any and get
	 * the GPIO from there.
	 */
	gpiod = devm_gpiod_get_index(dev, NULL, idx, flags);
	if (!IS_ERR(gpiod)) {
		gpiod_set_consumer_name(gpiod, template->name);
		return gpiod;
	}
	if (PTR_ERR(gpiod) != -ENOENT)
		return gpiod;

	/*
	 * This is the legacy code path for platform code that
	 * still uses GPIO numbers. Ultimately we would like to get
	 * rid of this block completely.
	 */

	/* skip leds that aren't available */
	if (!gpio_is_valid(template->gpio))
		return ERR_PTR(-ENOENT);

	if (template->active_low)
		flags |= GPIOF_ACTIVE_LOW;

	ret = devm_gpio_request_one(dev, template->gpio, flags,
				    template->name);
	if (ret < 0)
		return ERR_PTR(ret);

	gpiod = gpio_to_desc(template->gpio);
	if (!gpiod)
		return ERR_PTR(-EINVAL);

	return gpiod;
}