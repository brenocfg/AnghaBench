#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * release; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct mcb_bus {int bus_nr; TYPE_1__ dev; int /*<<< orphan*/  carrier; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mcb_bus* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcb_bus*) ; 
 struct mcb_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcb_bus_type ; 
 int /*<<< orphan*/  mcb_carrier_device_type ; 
 int /*<<< orphan*/  mcb_free_bus ; 
 int /*<<< orphan*/  mcb_ida ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct mcb_bus *mcb_alloc_bus(struct device *carrier)
{
	struct mcb_bus *bus;
	int bus_nr;
	int rc;

	bus = kzalloc(sizeof(struct mcb_bus), GFP_KERNEL);
	if (!bus)
		return ERR_PTR(-ENOMEM);

	bus_nr = ida_simple_get(&mcb_ida, 0, 0, GFP_KERNEL);
	if (bus_nr < 0) {
		rc = bus_nr;
		goto err_free;
	}

	bus->bus_nr = bus_nr;
	bus->carrier = get_device(carrier);

	device_initialize(&bus->dev);
	bus->dev.parent = carrier;
	bus->dev.bus = &mcb_bus_type;
	bus->dev.type = &mcb_carrier_device_type;
	bus->dev.release = &mcb_free_bus;

	dev_set_name(&bus->dev, "mcb:%d", bus_nr);
	rc = device_add(&bus->dev);
	if (rc)
		goto err_free;

	return bus;
err_free:
	put_device(carrier);
	kfree(bus);
	return ERR_PTR(rc);
}