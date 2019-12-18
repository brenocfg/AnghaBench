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
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  manager_add_attribute ; 
 int /*<<< orphan*/  manager_dump_attribute ; 
 int /*<<< orphan*/  manager_remove_attribute ; 
 int /*<<< orphan*/  manager_sysfs_init_attribute (struct kobject*,int /*<<< orphan*/ *) ; 

void gb_audio_manager_sysfs_init(struct kobject *kobj)
{
	manager_sysfs_init_attribute(kobj, &manager_add_attribute);
	manager_sysfs_init_attribute(kobj, &manager_remove_attribute);
	manager_sysfs_init_attribute(kobj, &manager_dump_attribute);
}