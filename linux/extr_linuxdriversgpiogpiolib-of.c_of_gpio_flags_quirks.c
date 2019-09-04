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
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_REGULATOR ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int OF_GPIO_OPEN_DRAIN ; 
 int OF_GPIO_SINGLE_ENDED ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_full_name (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void of_gpio_flags_quirks(struct device_node *np,
				 enum of_gpio_flags *flags)
{
	/*
	 * Some GPIO fixed regulator quirks.
	 * Note that active low is the default.
	 */
	if (IS_ENABLED(CONFIG_REGULATOR) &&
	    (of_device_is_compatible(np, "regulator-fixed") ||
	     of_device_is_compatible(np, "reg-fixed-voltage") ||
	     of_device_is_compatible(np, "regulator-gpio"))) {
		/*
		 * The regulator GPIO handles are specified such that the
		 * presence or absence of "enable-active-high" solely controls
		 * the polarity of the GPIO line. Any phandle flags must
		 * be actively ignored.
		 */
		if (*flags & OF_GPIO_ACTIVE_LOW) {
			pr_warn("%s GPIO handle specifies active low - ignored\n",
				of_node_full_name(np));
			*flags &= ~OF_GPIO_ACTIVE_LOW;
		}
		if (!of_property_read_bool(np, "enable-active-high"))
			*flags |= OF_GPIO_ACTIVE_LOW;
	}
	/*
	 * Legacy open drain handling for fixed voltage regulators.
	 */
	if (IS_ENABLED(CONFIG_REGULATOR) &&
	    of_device_is_compatible(np, "reg-fixed-voltage") &&
	    of_property_read_bool(np, "gpio-open-drain")) {
		*flags |= (OF_GPIO_SINGLE_ENDED | OF_GPIO_OPEN_DRAIN);
		pr_info("%s uses legacy open drain flag - update the DTS if you can\n",
			of_node_full_name(np));
	}
}