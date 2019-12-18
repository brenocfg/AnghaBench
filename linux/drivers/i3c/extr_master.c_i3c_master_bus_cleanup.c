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
struct i3c_master_controller {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bus_cleanup ) (struct i3c_master_controller*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i3c_master_detach_free_devs (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  stub1 (struct i3c_master_controller*) ; 

__attribute__((used)) static void i3c_master_bus_cleanup(struct i3c_master_controller *master)
{
	if (master->ops->bus_cleanup)
		master->ops->bus_cleanup(master);

	i3c_master_detach_free_devs(master);
}