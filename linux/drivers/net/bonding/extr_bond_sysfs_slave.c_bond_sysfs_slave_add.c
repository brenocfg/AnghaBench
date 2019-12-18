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
struct slave_attribute {int /*<<< orphan*/  attr; } ;
struct slave {int /*<<< orphan*/  kobj; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct slave_attribute** slave_attrs ; 
 int /*<<< orphan*/  slave_ktype ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bond_sysfs_slave_add(struct slave *slave)
{
	const struct slave_attribute **a;
	int err;

	err = kobject_init_and_add(&slave->kobj, &slave_ktype,
				   &(slave->dev->dev.kobj), "bonding_slave");
	if (err)
		return err;

	for (a = slave_attrs; *a; ++a) {
		err = sysfs_create_file(&slave->kobj, &((*a)->attr));
		if (err) {
			kobject_put(&slave->kobj);
			return err;
		}
	}

	return 0;
}