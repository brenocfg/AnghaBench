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
struct gpio_desc {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  prop_name ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ENOENT ; 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_OPEN_DRAIN ; 
 unsigned long GPIO_OPEN_SOURCE ; 
 unsigned long GPIO_PULL_DOWN ; 
 unsigned long GPIO_PULL_UP ; 
 unsigned long GPIO_TRANSITORY ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int OF_GPIO_OPEN_DRAIN ; 
 int OF_GPIO_PULL_DOWN ; 
 int OF_GPIO_PULL_UP ; 
 int OF_GPIO_SINGLE_ENDED ; 
 int OF_GPIO_TRANSITORY ; 
 int /*<<< orphan*/  PTR_ERR (struct gpio_desc*) ; 
 char** gpio_suffixes ; 
 struct gpio_desc* of_find_arizona_gpio (struct device*,char const*,int*) ; 
 struct gpio_desc* of_find_regulator_gpio (struct device*,char const*,int*) ; 
 struct gpio_desc* of_find_spi_cs_gpio (struct device*,char const*,unsigned int,unsigned long*) ; 
 struct gpio_desc* of_find_spi_gpio (struct device*,char const*,int*) ; 
 struct gpio_desc* of_get_named_gpiod_flags (int /*<<< orphan*/ ,char*,unsigned int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

struct gpio_desc *of_find_gpio(struct device *dev, const char *con_id,
			       unsigned int idx, unsigned long *flags)
{
	char prop_name[32]; /* 32 is max size of property name */
	enum of_gpio_flags of_flags;
	struct gpio_desc *desc;
	unsigned int i;

	/* Try GPIO property "foo-gpios" and "foo-gpio" */
	for (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snprintf(prop_name, sizeof(prop_name), "%s-%s", con_id,
				 gpio_suffixes[i]);
		else
			snprintf(prop_name, sizeof(prop_name), "%s",
				 gpio_suffixes[i]);

		desc = of_get_named_gpiod_flags(dev->of_node, prop_name, idx,
						&of_flags);

		if (!IS_ERR(desc) || PTR_ERR(desc) != -ENOENT)
			break;
	}

	if (IS_ERR(desc) && PTR_ERR(desc) == -ENOENT) {
		/* Special handling for SPI GPIOs if used */
		desc = of_find_spi_gpio(dev, con_id, &of_flags);
	}

	if (IS_ERR(desc) && PTR_ERR(desc) == -ENOENT) {
		/* This quirk looks up flags and all */
		desc = of_find_spi_cs_gpio(dev, con_id, idx, flags);
		if (!IS_ERR(desc))
			return desc;
	}

	if (IS_ERR(desc) && PTR_ERR(desc) == -ENOENT) {
		/* Special handling for regulator GPIOs if used */
		desc = of_find_regulator_gpio(dev, con_id, &of_flags);
	}

	if (IS_ERR(desc) && PTR_ERR(desc) == -ENOENT)
		desc = of_find_arizona_gpio(dev, con_id, &of_flags);

	if (IS_ERR(desc))
		return desc;

	if (of_flags & OF_GPIO_ACTIVE_LOW)
		*flags |= GPIO_ACTIVE_LOW;

	if (of_flags & OF_GPIO_SINGLE_ENDED) {
		if (of_flags & OF_GPIO_OPEN_DRAIN)
			*flags |= GPIO_OPEN_DRAIN;
		else
			*flags |= GPIO_OPEN_SOURCE;
	}

	if (of_flags & OF_GPIO_TRANSITORY)
		*flags |= GPIO_TRANSITORY;

	if (of_flags & OF_GPIO_PULL_UP)
		*flags |= GPIO_PULL_UP;
	if (of_flags & OF_GPIO_PULL_DOWN)
		*flags |= GPIO_PULL_DOWN;

	return desc;
}