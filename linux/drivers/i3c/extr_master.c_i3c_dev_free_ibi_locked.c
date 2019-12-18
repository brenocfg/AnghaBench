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
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_ibi ) (struct i3c_dev_desc*) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_dev_disable_ibi_locked (struct i3c_dev_desc*) ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct i3c_dev_desc*) ; 

void i3c_dev_free_ibi_locked(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *master = i3c_dev_get_master(dev);

	if (!dev->ibi)
		return;

	if (WARN_ON(dev->ibi->enabled))
		WARN_ON(i3c_dev_disable_ibi_locked(dev));

	master->ops->free_ibi(dev);
	kfree(dev->ibi);
	dev->ibi = NULL;
}