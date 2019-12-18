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
struct module {int dummy; } ;
struct ipack_bus_ops {int dummy; } ;
struct ipack_bus_device {int bus_nr; int slots; struct module* owner; struct ipack_bus_ops const* ops; struct device* parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipack_ida ; 
 int /*<<< orphan*/  kfree (struct ipack_bus_device*) ; 
 struct ipack_bus_device* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ipack_bus_device *ipack_bus_register(struct device *parent, int slots,
					    const struct ipack_bus_ops *ops,
					    struct module *owner)
{
	int bus_nr;
	struct ipack_bus_device *bus;

	bus = kzalloc(sizeof(*bus), GFP_KERNEL);
	if (!bus)
		return NULL;

	bus_nr = ida_simple_get(&ipack_ida, 0, 0, GFP_KERNEL);
	if (bus_nr < 0) {
		kfree(bus);
		return NULL;
	}

	bus->bus_nr = bus_nr;
	bus->parent = parent;
	bus->slots = slots;
	bus->ops = ops;
	bus->owner = owner;
	return bus;
}