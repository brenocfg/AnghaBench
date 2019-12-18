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
struct i3c_master_controller {int dummy; } ;
struct TYPE_3__ {struct i3c_master_controller* master; } ;
struct i2c_dev_desc {int /*<<< orphan*/  lvr; int /*<<< orphan*/  addr; struct i2c_dev_boardinfo const* boardinfo; TYPE_1__ common; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct i2c_dev_boardinfo {int /*<<< orphan*/  lvr; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i2c_dev_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct i2c_dev_desc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i2c_dev_desc *
i3c_master_alloc_i2c_dev(struct i3c_master_controller *master,
			 const struct i2c_dev_boardinfo *boardinfo)
{
	struct i2c_dev_desc *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	dev->common.master = master;
	dev->boardinfo = boardinfo;
	dev->addr = boardinfo->base.addr;
	dev->lvr = boardinfo->lvr;

	return dev;
}