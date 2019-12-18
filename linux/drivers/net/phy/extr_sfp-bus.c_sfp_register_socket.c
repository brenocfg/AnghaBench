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
struct sfp_socket_ops {int dummy; } ;
struct sfp_bus {scalar_t__ upstream_ops; struct sfp_socket_ops const* socket_ops; struct sfp* sfp; struct device* sfp_dev; } ;
struct sfp {int dummy; } ;
struct device {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct sfp_bus* sfp_bus_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_bus_put (struct sfp_bus*) ; 
 int sfp_register_bus (struct sfp_bus*) ; 
 int /*<<< orphan*/  sfp_socket_clear (struct sfp_bus*) ; 

struct sfp_bus *sfp_register_socket(struct device *dev, struct sfp *sfp,
				    const struct sfp_socket_ops *ops)
{
	struct sfp_bus *bus = sfp_bus_get(dev->fwnode);
	int ret = 0;

	if (bus) {
		rtnl_lock();
		bus->sfp_dev = dev;
		bus->sfp = sfp;
		bus->socket_ops = ops;

		if (bus->upstream_ops) {
			ret = sfp_register_bus(bus);
			if (ret)
				sfp_socket_clear(bus);
		}
		rtnl_unlock();
	}

	if (ret) {
		sfp_bus_put(bus);
		bus = NULL;
	}

	return bus;
}