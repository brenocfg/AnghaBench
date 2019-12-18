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
struct port {scalar_t__ is_enabled; struct port* next_port_in_aggregator; } ;
struct aggregator {struct port* lag_ports; } ;

/* Variables and functions */

__attribute__((used)) static int __agg_active_ports(struct aggregator *agg)
{
	struct port *port;
	int active = 0;

	for (port = agg->lag_ports; port;
	     port = port->next_port_in_aggregator) {
		if (port->is_enabled)
			active++;
	}

	return active;
}