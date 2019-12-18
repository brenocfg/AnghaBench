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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {int phys_port_cnt; TYPE_1__ dev; } ;
struct mlx4_ib_dev {void* iov_parent; void* ports_parent; TYPE_2__ ib_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int add_port_entries (struct mlx4_ib_dev*,int) ; 
 void* kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kobject_get (void*) ; 
 int /*<<< orphan*/  kobject_put (void*) ; 
 int /*<<< orphan*/  mlx4_is_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int register_pkey_tree (struct mlx4_ib_dev*) ; 

int mlx4_ib_device_register_sysfs(struct mlx4_ib_dev *dev)
{
	int i;
	int ret = 0;

	if (!mlx4_is_master(dev->dev))
		return 0;

	dev->iov_parent = kobject_create_and_add("iov", &dev->ib_dev.dev.kobj);
	if (!dev->iov_parent) {
		ret = -ENOMEM;
		goto err;
	}
	dev->ports_parent =
		kobject_create_and_add("ports",
				       kobject_get(dev->iov_parent));
	if (!dev->ports_parent) {
		ret = -ENOMEM;
		goto err_ports;
	}

	for (i = 1; i <= dev->ib_dev.phys_port_cnt; ++i) {
		ret = add_port_entries(dev, i);
		if (ret)
			goto err_add_entries;
	}

	ret = register_pkey_tree(dev);
	if (ret)
		goto err_add_entries;
	return 0;

err_add_entries:
	kobject_put(dev->ports_parent);

err_ports:
	kobject_put(dev->iov_parent);
err:
	pr_err("mlx4_ib_device_register_sysfs error (%d)\n", ret);
	return ret;
}