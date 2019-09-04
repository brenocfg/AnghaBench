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
typedef  enum gpio_lookup_flags { ____Placeholder_gpio_lookup_flags } gpio_lookup_flags ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int GPIO_ACTIVE_LOW ; 
 int GPIO_OPEN_DRAIN ; 
 int GPIO_OPEN_SOURCE ; 
 int GPIO_TRANSITORY ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int OF_GPIO_OPEN_DRAIN ; 
 int OF_GPIO_SINGLE_ENDED ; 
 int OF_GPIO_TRANSITORY ; 
 int /*<<< orphan*/  PTR_ERR (struct gpio_desc*) ; 
 char** gpio_suffixes ; 
 struct gpio_desc* of_find_regulator_gpio (struct device*,char const*,int*) ; 
 struct gpio_desc* of_find_spi_gpio (struct device*,char const*,int*) ; 
 struct gpio_desc* of_get_named_gpiod_flags (int /*<<< orphan*/ ,char*,unsigned int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

struct gpio_desc *of_find_gpio(struct device *dev, const char *con_id,
			       unsigned int idx,
			       enum gpio_lookup_flags *flags)
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
		/*
		 * -EPROBE_DEFER in our case means that we found a
		 * valid GPIO property, but no controller has been
		 * registered so far.
		 *
		 * This means we don't need to look any further for
		 * alternate name conventions, and we should really
		 * preserve the return code for our user to be able to
		 * retry probing later.
		 */
		if (IS_ERR(desc) && PTR_ERR(desc) == -EPROBE_DEFER)
			return desc;

		if (!IS_ERR(desc) || (PTR_ERR(desc) != -ENOENT))
			break;
	}

	/* Special handling for SPI GPIOs if used */
	if (IS_ERR(desc))
		desc = of_find_spi_gpio(dev, con_id, &of_flags);

	/* Special handling for regulator GPIOs if used */
	if (IS_ERR(desc) && PTR_ERR(desc) != -EPROBE_DEFER)
		desc = of_find_regulator_gpio(dev, con_id, &of_flags);

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

	return desc;
}