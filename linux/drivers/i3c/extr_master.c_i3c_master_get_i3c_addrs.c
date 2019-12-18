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
struct i3c_master_controller {int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  static_addr; int /*<<< orphan*/  dyn_addr; } ;
struct i3c_dev_desc {TYPE_2__ info; TYPE_1__* boardinfo; } ;
typedef  enum i3c_addr_slot_status { ____Placeholder_i3c_addr_slot_status } i3c_addr_slot_status ;
struct TYPE_3__ {int /*<<< orphan*/  init_dyn_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int I3C_ADDR_SLOT_FREE ; 
 int I3C_ADDR_SLOT_I3C_DEV ; 
 int i3c_bus_get_addr_slot_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_bus_set_addr_slot_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 

__attribute__((used)) static int i3c_master_get_i3c_addrs(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *master = i3c_dev_get_master(dev);
	enum i3c_addr_slot_status status;

	if (!dev->info.static_addr && !dev->info.dyn_addr)
		return 0;

	if (dev->info.static_addr) {
		status = i3c_bus_get_addr_slot_status(&master->bus,
						      dev->info.static_addr);
		if (status != I3C_ADDR_SLOT_FREE)
			return -EBUSY;

		i3c_bus_set_addr_slot_status(&master->bus,
					     dev->info.static_addr,
					     I3C_ADDR_SLOT_I3C_DEV);
	}

	/*
	 * ->init_dyn_addr should have been reserved before that, so, if we're
	 * trying to apply a pre-reserved dynamic address, we should not try
	 * to reserve the address slot a second time.
	 */
	if (dev->info.dyn_addr &&
	    (!dev->boardinfo ||
	     dev->boardinfo->init_dyn_addr != dev->info.dyn_addr)) {
		status = i3c_bus_get_addr_slot_status(&master->bus,
						      dev->info.dyn_addr);
		if (status != I3C_ADDR_SLOT_FREE)
			goto err_release_static_addr;

		i3c_bus_set_addr_slot_status(&master->bus, dev->info.dyn_addr,
					     I3C_ADDR_SLOT_I3C_DEV);
	}

	return 0;

err_release_static_addr:
	if (dev->info.static_addr)
		i3c_bus_set_addr_slot_status(&master->bus,
					     dev->info.static_addr,
					     I3C_ADDR_SLOT_FREE);

	return -EBUSY;
}