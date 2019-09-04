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
struct slave_attribute {int /*<<< orphan*/  attr; } ;
struct slave {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct slave_attribute** slave_attrs ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bond_sysfs_slave_del(struct slave *slave)
{
	const struct slave_attribute **a;

	for (a = slave_attrs; *a; ++a)
		sysfs_remove_file(&slave->kobj, &((*a)->attr));

	kobject_put(&slave->kobj);
}