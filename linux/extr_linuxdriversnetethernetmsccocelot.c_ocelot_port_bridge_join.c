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
struct ocelot_port {int /*<<< orphan*/  chip_port; struct ocelot* ocelot; } ;
struct ocelot {int /*<<< orphan*/  bridge_mask; struct net_device* hw_bridge_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 

__attribute__((used)) static int ocelot_port_bridge_join(struct ocelot_port *ocelot_port,
				   struct net_device *bridge)
{
	struct ocelot *ocelot = ocelot_port->ocelot;

	if (!ocelot->bridge_mask) {
		ocelot->hw_bridge_dev = bridge;
	} else {
		if (ocelot->hw_bridge_dev != bridge)
			/* This is adding the port to a second bridge, this is
			 * unsupported */
			return -ENODEV;
	}

	ocelot->bridge_mask |= BIT(ocelot_port->chip_port);

	return 0;
}