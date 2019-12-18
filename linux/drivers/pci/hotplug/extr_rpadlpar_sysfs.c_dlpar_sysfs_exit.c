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

/* Variables and functions */
 int /*<<< orphan*/  dlpar_attr_group ; 
 int /*<<< orphan*/  dlpar_kobj ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dlpar_sysfs_exit(void)
{
	sysfs_remove_group(dlpar_kobj, &dlpar_attr_group);
	kobject_put(dlpar_kobj);
}