#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct property {TYPE_2__ attr; } ;
struct device_node {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SYSFS ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,TYPE_2__*) ; 

void __of_sysfs_remove_bin_file(struct device_node *np, struct property *prop)
{
	if (!IS_ENABLED(CONFIG_SYSFS))
		return;

	sysfs_remove_bin_file(&np->kobj, &prop->attr);
	kfree(prop->attr.attr.name);
}