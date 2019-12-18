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
struct TYPE_2__ {struct i3c_dev_desc* cur_master; } ;
struct i3c_master_controller {struct i3c_dev_desc* this; TYPE_1__ bus; scalar_t__ secondary; } ;
struct i3c_device_info {int /*<<< orphan*/  bcr; int /*<<< orphan*/  dyn_addr; } ;
struct i3c_dev_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I3C_BCR_DEVICE_ROLE (int /*<<< orphan*/ ) ; 
 scalar_t__ I3C_BCR_I3C_MASTER ; 
 scalar_t__ IS_ERR (struct i3c_dev_desc*) ; 
 int PTR_ERR (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_bus_dev_addr_is_avail (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct i3c_dev_desc* i3c_master_alloc_i3c_dev (struct i3c_master_controller*,struct i3c_device_info const*) ; 
 int i3c_master_attach_i3c_dev (struct i3c_master_controller*,struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_master_free_i3c_dev (struct i3c_dev_desc*) ; 

int i3c_master_set_info(struct i3c_master_controller *master,
			const struct i3c_device_info *info)
{
	struct i3c_dev_desc *i3cdev;
	int ret;

	if (!i3c_bus_dev_addr_is_avail(&master->bus, info->dyn_addr))
		return -EINVAL;

	if (I3C_BCR_DEVICE_ROLE(info->bcr) == I3C_BCR_I3C_MASTER &&
	    master->secondary)
		return -EINVAL;

	if (master->this)
		return -EINVAL;

	i3cdev = i3c_master_alloc_i3c_dev(master, info);
	if (IS_ERR(i3cdev))
		return PTR_ERR(i3cdev);

	master->this = i3cdev;
	master->bus.cur_master = master->this;

	ret = i3c_master_attach_i3c_dev(master, i3cdev);
	if (ret)
		goto err_free_dev;

	return 0;

err_free_dev:
	i3c_master_free_i3c_dev(i3cdev);

	return ret;
}