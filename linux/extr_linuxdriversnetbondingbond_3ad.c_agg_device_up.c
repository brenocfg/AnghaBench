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
struct port {TYPE_1__* slave; struct port* next_port_in_aggregator; } ;
struct aggregator {struct port* lag_ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int agg_device_up(const struct aggregator *agg)
{
	struct port *port = agg->lag_ports;

	if (!port)
		return 0;

	for (port = agg->lag_ports; port;
	     port = port->next_port_in_aggregator) {
		if (netif_running(port->slave->dev) &&
		    netif_carrier_ok(port->slave->dev))
			return 1;
	}

	return 0;
}