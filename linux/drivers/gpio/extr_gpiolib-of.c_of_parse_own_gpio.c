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
typedef  unsigned int u32 ;
struct of_phandle_args {unsigned int args_count; int /*<<< orphan*/ * args; struct device_node* np; } ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {struct device_node* of_node; } ;
struct device_node {char* name; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EINVAL ; 
 struct gpio_desc* ERR_PTR (int) ; 
 int GPIOD_IN ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_LOOKUP_FLAGS_DEFAULT ; 
 unsigned long GPIO_TRANSITORY ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int OF_GPIO_TRANSITORY ; 
 int /*<<< orphan*/  desc_to_gpio (struct gpio_desc*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,unsigned int,int /*<<< orphan*/ *) ; 
 struct gpio_desc* of_xlate_and_get_gpiod_flags (struct gpio_chip*,struct of_phandle_args*,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,struct device_node*) ; 

__attribute__((used)) static struct gpio_desc *of_parse_own_gpio(struct device_node *np,
					   struct gpio_chip *chip,
					   unsigned int idx, const char **name,
					   unsigned long *lflags,
					   enum gpiod_flags *dflags)
{
	struct device_node *chip_np;
	enum of_gpio_flags xlate_flags;
	struct of_phandle_args gpiospec;
	struct gpio_desc *desc;
	unsigned int i;
	u32 tmp;
	int ret;

	chip_np = chip->of_node;
	if (!chip_np)
		return ERR_PTR(-EINVAL);

	xlate_flags = 0;
	*lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	*dflags = 0;

	ret = of_property_read_u32(chip_np, "#gpio-cells", &tmp);
	if (ret)
		return ERR_PTR(ret);

	gpiospec.np = chip_np;
	gpiospec.args_count = tmp;

	for (i = 0; i < tmp; i++) {
		ret = of_property_read_u32_index(np, "gpios", idx * tmp + i,
						 &gpiospec.args[i]);
		if (ret)
			return ERR_PTR(ret);
	}

	desc = of_xlate_and_get_gpiod_flags(chip, &gpiospec, &xlate_flags);
	if (IS_ERR(desc))
		return desc;

	if (xlate_flags & OF_GPIO_ACTIVE_LOW)
		*lflags |= GPIO_ACTIVE_LOW;
	if (xlate_flags & OF_GPIO_TRANSITORY)
		*lflags |= GPIO_TRANSITORY;

	if (of_property_read_bool(np, "input"))
		*dflags |= GPIOD_IN;
	else if (of_property_read_bool(np, "output-low"))
		*dflags |= GPIOD_OUT_LOW;
	else if (of_property_read_bool(np, "output-high"))
		*dflags |= GPIOD_OUT_HIGH;
	else {
		pr_warn("GPIO line %d (%pOFn): no hogging state specified, bailing out\n",
			desc_to_gpio(desc), np);
		return ERR_PTR(-EINVAL);
	}

	if (name && of_property_read_string(np, "line-name", name))
		*name = np->name;

	return desc;
}