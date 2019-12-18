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
struct mctrl_gpios {int /*<<< orphan*/ * gpio; } ;
struct device {int dummy; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mctrl_gpios* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct mctrl_gpios* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int UART_GPIO_MAX ; 
 int device_property_present (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_index_optional (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct mctrl_gpios* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 TYPE_1__* mctrl_gpios_desc ; 

struct mctrl_gpios *mctrl_gpio_init_noauto(struct device *dev, unsigned int idx)
{
	struct mctrl_gpios *gpios;
	enum mctrl_gpio_idx i;

	gpios = devm_kzalloc(dev, sizeof(*gpios), GFP_KERNEL);
	if (!gpios)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < UART_GPIO_MAX; i++) {
		char *gpio_str;
		bool present;

		/* Check if GPIO property exists and continue if not */
		gpio_str = kasprintf(GFP_KERNEL, "%s-gpios",
				     mctrl_gpios_desc[i].name);
		if (!gpio_str)
			continue;

		present = device_property_present(dev, gpio_str);
		kfree(gpio_str);
		if (!present)
			continue;

		gpios->gpio[i] =
			devm_gpiod_get_index_optional(dev,
						      mctrl_gpios_desc[i].name,
						      idx,
						      mctrl_gpios_desc[i].flags);

		if (IS_ERR(gpios->gpio[i]))
			return ERR_CAST(gpios->gpio[i]);
	}

	return gpios;
}