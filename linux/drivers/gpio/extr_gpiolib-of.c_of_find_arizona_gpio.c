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
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MFD_ARIZONA ; 
 int /*<<< orphan*/  ENOENT ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct gpio_desc* of_get_named_gpiod_flags (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct gpio_desc *of_find_arizona_gpio(struct device *dev,
					      const char *con_id,
					      enum of_gpio_flags *of_flags)
{
	if (!IS_ENABLED(CONFIG_MFD_ARIZONA))
		return ERR_PTR(-ENOENT);

	if (!con_id || strcmp(con_id, "wlf,reset"))
		return ERR_PTR(-ENOENT);

	return of_get_named_gpiod_flags(dev->of_node, con_id, 0, of_flags);
}