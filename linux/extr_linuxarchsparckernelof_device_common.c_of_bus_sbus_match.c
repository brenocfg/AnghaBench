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
struct device_node {struct device_node* parent; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int of_bus_sbus_match(struct device_node *np)
{
	struct device_node *dp = np;

	while (dp) {
		if (!strcmp(dp->name, "sbus") ||
		    !strcmp(dp->name, "sbi"))
			return 1;

		/* Have a look at use_1to1_mapping().  We're trying
		 * to match SBUS if that's the top-level bus and we
		 * don't have some intervening real bus that provides
		 * ranges based translations.
		 */
		if (of_find_property(dp, "ranges", NULL) != NULL)
			break;

		dp = dp->parent;
	}

	return 0;
}