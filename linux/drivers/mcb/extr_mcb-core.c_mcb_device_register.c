#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/ * bus; } ;
struct mcb_device {int id; TYPE_2__ dev; int /*<<< orphan*/  var; int /*<<< orphan*/  group; int /*<<< orphan*/  inst; int /*<<< orphan*/  dma_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct mcb_bus {int /*<<< orphan*/  bus_nr; int /*<<< orphan*/  carrier; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  mcb_bus_get (struct mcb_bus*) ; 
 int /*<<< orphan*/  mcb_bus_type ; 
 int /*<<< orphan*/  mcb_release_dev ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,int) ; 

int mcb_device_register(struct mcb_bus *bus, struct mcb_device *dev)
{
	int ret;
	int device_id;

	device_initialize(&dev->dev);
	mcb_bus_get(bus);
	dev->dev.bus = &mcb_bus_type;
	dev->dev.parent = bus->dev.parent;
	dev->dev.release = mcb_release_dev;
	dev->dma_dev = bus->carrier;

	device_id = dev->id;
	dev_set_name(&dev->dev, "mcb%d-16z%03d-%d:%d:%d",
		bus->bus_nr, device_id, dev->inst, dev->group, dev->var);

	ret = device_add(&dev->dev);
	if (ret < 0) {
		pr_err("Failed registering device 16z%03d on bus mcb%d (%d)\n",
			device_id, bus->bus_nr, ret);
		goto out;
	}

	return 0;

out:

	return ret;
}