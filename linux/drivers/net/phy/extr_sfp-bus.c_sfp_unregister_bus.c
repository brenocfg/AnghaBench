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
struct sfp_upstream_ops {int /*<<< orphan*/  (* disconnect_phy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* detach ) (int /*<<< orphan*/ ,struct sfp_bus*) ;} ;
struct sfp_bus {int registered; int /*<<< orphan*/  upstream; scalar_t__ phydev; int /*<<< orphan*/  sfp; TYPE_1__* socket_ops; scalar_t__ started; struct sfp_upstream_ops* upstream_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sfp_bus*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_unregister_bus(struct sfp_bus *bus)
{
	const struct sfp_upstream_ops *ops = bus->upstream_ops;

	if (bus->registered) {
		bus->upstream_ops->detach(bus->upstream, bus);
		if (bus->started)
			bus->socket_ops->stop(bus->sfp);
		bus->socket_ops->detach(bus->sfp);
		if (bus->phydev && ops && ops->disconnect_phy)
			ops->disconnect_phy(bus->upstream);
	}
	bus->registered = false;
}