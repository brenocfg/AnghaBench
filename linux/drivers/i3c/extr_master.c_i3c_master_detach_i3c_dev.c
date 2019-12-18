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
struct i3c_master_controller {TYPE_1__* ops; struct i3c_dev_desc* this; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct i3c_dev_desc {TYPE_2__ common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* detach_i3c_dev ) (struct i3c_dev_desc*) ;} ;

/* Variables and functions */
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_master_put_i3c_addrs (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct i3c_dev_desc*) ; 

__attribute__((used)) static void i3c_master_detach_i3c_dev(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *master = i3c_dev_get_master(dev);

	/* Do not detach the master device itself. */
	if (master->this != dev && master->ops->detach_i3c_dev)
		master->ops->detach_i3c_dev(dev);

	i3c_master_put_i3c_addrs(dev);
	list_del(&dev->common.node);
}