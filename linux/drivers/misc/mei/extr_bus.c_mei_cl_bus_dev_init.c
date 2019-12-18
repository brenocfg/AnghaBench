#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mei_me_client {int bus_added; } ;
struct mei_device {int /*<<< orphan*/  device_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  cl_bus_lock; } ;
struct mei_cl_device {int /*<<< orphan*/  bus_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mei_cl_device* mei_cl_bus_dev_alloc (struct mei_device*,struct mei_me_client*) ; 
 int /*<<< orphan*/  mei_me_cl_uuid (struct mei_me_client*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_cl_bus_dev_init(struct mei_device *bus,
				struct mei_me_client *me_cl)
{
	struct mei_cl_device *cldev;

	WARN_ON(!mutex_is_locked(&bus->cl_bus_lock));

	dev_dbg(bus->dev, "initializing %pUl", mei_me_cl_uuid(me_cl));

	if (me_cl->bus_added)
		return;

	cldev = mei_cl_bus_dev_alloc(bus, me_cl);
	if (!cldev)
		return;

	me_cl->bus_added = true;
	list_add_tail(&cldev->bus_list, &bus->device_list);

}