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
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  platform_rev; int /*<<< orphan*/  platform_id; int /*<<< orphan*/  platform_oem; struct attribute attr_props; int /*<<< orphan*/  generation_count; struct attribute attr_genid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 TYPE_1__ sys_props ; 
 int /*<<< orphan*/  sysfs_show_32bit_val (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_show_64bit_prop (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sysprops_show(struct kobject *kobj, struct attribute *attr,
		char *buffer)
{
	ssize_t ret;

	/* Making sure that the buffer is an empty string */
	buffer[0] = 0;

	if (attr == &sys_props.attr_genid) {
		ret = sysfs_show_32bit_val(buffer, sys_props.generation_count);
	} else if (attr == &sys_props.attr_props) {
		sysfs_show_64bit_prop(buffer, "platform_oem",
				sys_props.platform_oem);
		sysfs_show_64bit_prop(buffer, "platform_id",
				sys_props.platform_id);
		ret = sysfs_show_64bit_prop(buffer, "platform_rev",
				sys_props.platform_rev);
	} else {
		ret = -EINVAL;
	}

	return ret;
}