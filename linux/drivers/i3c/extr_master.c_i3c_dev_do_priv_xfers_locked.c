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
struct i3c_priv_xfer {int dummy; } ;
struct i3c_master_controller {TYPE_1__* ops; } ;
struct i3c_dev_desc {int dummy; } ;
struct TYPE_2__ {int (* priv_xfers ) (struct i3c_dev_desc*,struct i3c_priv_xfer*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int stub1 (struct i3c_dev_desc*,struct i3c_priv_xfer*,int) ; 

int i3c_dev_do_priv_xfers_locked(struct i3c_dev_desc *dev,
				 struct i3c_priv_xfer *xfers,
				 int nxfers)
{
	struct i3c_master_controller *master;

	if (!dev)
		return -ENOENT;

	master = i3c_dev_get_master(dev);
	if (!master || !xfers)
		return -EINVAL;

	if (!master->ops->priv_xfers)
		return -ENOTSUPP;

	return master->ops->priv_xfers(dev, xfers, nxfers);
}