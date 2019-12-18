#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct kobj_attribute {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int sysfs_create_file (struct kobject*,TYPE_1__*) ; 

__attribute__((used)) static void manager_sysfs_init_attribute(struct kobject *kobj,
					 struct kobj_attribute *kattr)
{
	int err;

	err = sysfs_create_file(kobj, &kattr->attr);
	if (err) {
		pr_warn("creating the sysfs entry for %s failed: %d\n",
			kattr->attr.name, err);
	}
}