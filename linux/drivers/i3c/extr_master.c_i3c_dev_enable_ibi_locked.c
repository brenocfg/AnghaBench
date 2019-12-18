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
struct i3c_master_controller {TYPE_1__* ops; } ;
struct i3c_dev_desc {TYPE_2__* ibi; } ;
struct TYPE_4__ {int enabled; } ;
struct TYPE_3__ {int (* enable_ibi ) (struct i3c_dev_desc*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int stub1 (struct i3c_dev_desc*) ; 

int i3c_dev_enable_ibi_locked(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *master = i3c_dev_get_master(dev);
	int ret;

	if (!dev->ibi)
		return -EINVAL;

	ret = master->ops->enable_ibi(dev);
	if (!ret)
		dev->ibi->enabled = true;

	return ret;
}