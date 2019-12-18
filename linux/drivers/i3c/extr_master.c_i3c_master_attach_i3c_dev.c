#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  i3c; } ;
struct TYPE_9__ {TYPE_3__ devs; } ;
struct i3c_master_controller {TYPE_4__ bus; TYPE_1__* ops; struct i3c_dev_desc* this; } ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_10__ {int /*<<< orphan*/  dyn_addr; int /*<<< orphan*/  static_addr; } ;
struct i3c_dev_desc {TYPE_2__ common; TYPE_5__ info; } ;
struct TYPE_6__ {int (* attach_i3c_dev ) (struct i3c_dev_desc*) ;} ;

/* Variables and functions */
 int i3c_master_get_i3c_addrs (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_master_put_i3c_addrs (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (struct i3c_dev_desc*) ; 

__attribute__((used)) static int i3c_master_attach_i3c_dev(struct i3c_master_controller *master,
				     struct i3c_dev_desc *dev)
{
	int ret;

	/*
	 * We don't attach devices to the controller until they are
	 * addressable on the bus.
	 */
	if (!dev->info.static_addr && !dev->info.dyn_addr)
		return 0;

	ret = i3c_master_get_i3c_addrs(dev);
	if (ret)
		return ret;

	/* Do not attach the master device itself. */
	if (master->this != dev && master->ops->attach_i3c_dev) {
		ret = master->ops->attach_i3c_dev(dev);
		if (ret) {
			i3c_master_put_i3c_addrs(dev);
			return ret;
		}
	}

	list_add_tail(&dev->common.node, &master->bus.devs.i3c);

	return 0;
}