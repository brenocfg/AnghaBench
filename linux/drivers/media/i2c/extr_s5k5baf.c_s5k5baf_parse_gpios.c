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
struct s5k5baf_gpio {int gpio; int level; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int NUM_GPIOS ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const* const) ; 
 int of_get_named_gpio_flags (struct device_node*,char const* const,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int s5k5baf_parse_gpios(struct s5k5baf_gpio *gpios, struct device *dev)
{
	static const char * const names[] = {
		"stbyn-gpios",
		"rstn-gpios",
	};
	struct device_node *node = dev->of_node;
	enum of_gpio_flags flags;
	int ret, i;

	for (i = 0; i < NUM_GPIOS; ++i) {
		ret = of_get_named_gpio_flags(node, names[i], 0, &flags);
		if (ret < 0) {
			dev_err(dev, "no %s GPIO pin provided\n", names[i]);
			return ret;
		}
		gpios[i].gpio = ret;
		gpios[i].level = !(flags & OF_GPIO_ACTIVE_LOW);
	}

	return 0;
}