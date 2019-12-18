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
struct TYPE_4__ {int enabled; int /*<<< orphan*/  all_ibis_handled; int /*<<< orphan*/  pending_ibis; } ;
struct TYPE_3__ {int (* disable_ibi ) (struct i3c_dev_desc*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int i3c_dev_disable_ibi_locked(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *master;
	int ret;

	if (!dev->ibi)
		return -EINVAL;

	master = i3c_dev_get_master(dev);
	ret = master->ops->disable_ibi(dev);
	if (ret)
		return ret;

	reinit_completion(&dev->ibi->all_ibis_handled);
	if (atomic_read(&dev->ibi->pending_ibis))
		wait_for_completion(&dev->ibi->all_ibis_handled);

	dev->ibi->enabled = false;

	return 0;
}