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
struct driver_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ dev_attr_status ; 
 int /*<<< orphan*/  sysfs_remove_file (struct kobject*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_hw_sysfs_exit(struct driver_data *dd, struct kobject *kobj)
{
	if (!kobj || !dd)
		return -EINVAL;

	sysfs_remove_file(kobj, &dev_attr_status.attr);

	return 0;
}