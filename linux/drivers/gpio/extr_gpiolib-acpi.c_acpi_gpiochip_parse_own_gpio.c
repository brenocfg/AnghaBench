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
typedef  scalar_t__ u32 ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct acpi_gpio_chip {struct gpio_chip* chip; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 struct gpio_desc* ERR_PTR (int) ; 
 int GPIOD_IN ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_LOOKUP_FLAGS_DEFAULT ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 scalar_t__ fwnode_property_present (struct fwnode_handle*,char*) ; 
 int /*<<< orphan*/  fwnode_property_read_string (struct fwnode_handle*,char*,char const**) ; 
 int fwnode_property_read_u32_array (struct fwnode_handle*,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,scalar_t__) ; 

__attribute__((used)) static struct gpio_desc *
acpi_gpiochip_parse_own_gpio(struct acpi_gpio_chip *achip,
			     struct fwnode_handle *fwnode,
			     const char **name,
			     unsigned long *lflags,
			     enum gpiod_flags *dflags)
{
	struct gpio_chip *chip = achip->chip;
	struct gpio_desc *desc;
	u32 gpios[2];
	int ret;

	*lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	*dflags = 0;
	*name = NULL;

	ret = fwnode_property_read_u32_array(fwnode, "gpios", gpios,
					     ARRAY_SIZE(gpios));
	if (ret < 0)
		return ERR_PTR(ret);

	desc = gpiochip_get_desc(chip, gpios[0]);
	if (IS_ERR(desc))
		return desc;

	if (gpios[1])
		*lflags |= GPIO_ACTIVE_LOW;

	if (fwnode_property_present(fwnode, "input"))
		*dflags |= GPIOD_IN;
	else if (fwnode_property_present(fwnode, "output-low"))
		*dflags |= GPIOD_OUT_LOW;
	else if (fwnode_property_present(fwnode, "output-high"))
		*dflags |= GPIOD_OUT_HIGH;
	else
		return ERR_PTR(-EINVAL);

	fwnode_property_read_string(fwnode, "line-name", name);

	return desc;
}