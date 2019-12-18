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
struct i3c_master_controller {scalar_t__ wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  i3c; int /*<<< orphan*/  i2c; } ;
struct i3c_bus {TYPE_1__ devs; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 struct i3c_bus* dev_to_i3cbus (struct device*) ; 
 struct i3c_master_controller* dev_to_i3cmaster (struct device*) ; 
 int /*<<< orphan*/  i3c_bus_cleanup (struct i3c_bus*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i3c_masterdev_release(struct device *dev)
{
	struct i3c_master_controller *master = dev_to_i3cmaster(dev);
	struct i3c_bus *bus = dev_to_i3cbus(dev);

	if (master->wq)
		destroy_workqueue(master->wq);

	WARN_ON(!list_empty(&bus->devs.i2c) || !list_empty(&bus->devs.i3c));
	i3c_bus_cleanup(bus);

	of_node_put(dev->of_node);
}