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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  CONFIG_REGULATOR ; 
 int /*<<< orphan*/  ENOENT ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int match_string (char const**,int /*<<< orphan*/ ,char const*) ; 
 struct gpio_desc* of_get_named_gpiod_flags (struct device_node*,char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static struct gpio_desc *of_find_regulator_gpio(struct device *dev, const char *con_id,
						enum of_gpio_flags *of_flags)
{
	/* These are the connection IDs we accept as legacy GPIO phandles */
	const char *whitelist[] = {
		"wlf,ldoena", /* Arizona */
		"wlf,ldo1ena", /* WM8994 */
		"wlf,ldo2ena", /* WM8994 */
	};
	struct device_node *np = dev->of_node;
	struct gpio_desc *desc;
	int i;

	if (!IS_ENABLED(CONFIG_REGULATOR))
		return ERR_PTR(-ENOENT);

	if (!con_id)
		return ERR_PTR(-ENOENT);

	i = match_string(whitelist, ARRAY_SIZE(whitelist), con_id);
	if (i < 0)
		return ERR_PTR(-ENOENT);

	desc = of_get_named_gpiod_flags(np, con_id, 0, of_flags);
	return desc;
}