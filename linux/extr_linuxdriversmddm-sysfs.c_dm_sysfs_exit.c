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
struct mapped_device {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_get_completion_from_kobject (struct kobject*) ; 
 struct kobject* dm_kobject (struct mapped_device*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 

void dm_sysfs_exit(struct mapped_device *md)
{
	struct kobject *kobj = dm_kobject(md);
	kobject_put(kobj);
	wait_for_completion(dm_get_completion_from_kobject(kobj));
}