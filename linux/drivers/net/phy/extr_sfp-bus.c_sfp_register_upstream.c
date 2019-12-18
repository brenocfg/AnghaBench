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
struct sfp_upstream_ops {int dummy; } ;
struct sfp_bus {scalar_t__ sfp; void* upstream; struct sfp_upstream_ops const* upstream_ops; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct sfp_bus* sfp_bus_get (struct fwnode_handle*) ; 
 int /*<<< orphan*/  sfp_bus_put (struct sfp_bus*) ; 
 int sfp_register_bus (struct sfp_bus*) ; 
 int /*<<< orphan*/  sfp_upstream_clear (struct sfp_bus*) ; 

struct sfp_bus *sfp_register_upstream(struct fwnode_handle *fwnode,
				      void *upstream,
				      const struct sfp_upstream_ops *ops)
{
	struct sfp_bus *bus = sfp_bus_get(fwnode);
	int ret = 0;

	if (bus) {
		rtnl_lock();
		bus->upstream_ops = ops;
		bus->upstream = upstream;

		if (bus->sfp) {
			ret = sfp_register_bus(bus);
			if (ret)
				sfp_upstream_clear(bus);
		}
		rtnl_unlock();
	}

	if (ret) {
		sfp_bus_put(bus);
		bus = NULL;
	}

	return bus;
}