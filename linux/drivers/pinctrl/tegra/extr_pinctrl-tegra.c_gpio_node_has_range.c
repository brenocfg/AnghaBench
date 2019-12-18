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

/* Variables and functions */
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool gpio_node_has_range(const char *compatible)
{
	struct device_node *np;
	bool has_prop = false;

	np = of_find_compatible_node(NULL, NULL, compatible);
	if (!np)
		return has_prop;

	has_prop = of_find_property(np, "gpio-ranges", NULL);

	of_node_put(np);

	return has_prop;
}