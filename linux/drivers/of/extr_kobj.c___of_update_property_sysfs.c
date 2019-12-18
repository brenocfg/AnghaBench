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
struct property {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __of_add_property_sysfs (struct device_node*,struct property*) ; 
 int /*<<< orphan*/  __of_sysfs_remove_bin_file (struct device_node*,struct property*) ; 
 int /*<<< orphan*/  of_kset ; 

void __of_update_property_sysfs(struct device_node *np, struct property *newprop,
		struct property *oldprop)
{
	/* At early boot, bail out and defer setup to of_init() */
	if (!of_kset)
		return;

	if (oldprop)
		__of_sysfs_remove_bin_file(np, oldprop);
	__of_add_property_sysfs(np, newprop);
}