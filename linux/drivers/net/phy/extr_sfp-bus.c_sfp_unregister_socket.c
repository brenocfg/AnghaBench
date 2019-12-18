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
struct sfp_bus {scalar_t__ upstream_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sfp_bus_put (struct sfp_bus*) ; 
 int /*<<< orphan*/  sfp_socket_clear (struct sfp_bus*) ; 
 int /*<<< orphan*/  sfp_unregister_bus (struct sfp_bus*) ; 

void sfp_unregister_socket(struct sfp_bus *bus)
{
	rtnl_lock();
	if (bus->upstream_ops)
		sfp_unregister_bus(bus);
	sfp_socket_clear(bus);
	rtnl_unlock();

	sfp_bus_put(bus);
}