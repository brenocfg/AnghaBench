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
struct port {int sm_vars; struct port* next_port_in_aggregator; } ;
struct aggregator {struct port* lag_ports; } ;

/* Variables and functions */
 int AD_PORT_READY_N ; 

__attribute__((used)) static int __agg_ports_are_ready(struct aggregator *aggregator)
{
	struct port *port;
	int retval = 1;

	if (aggregator) {
		/* scan all ports in this aggregator to verfy if they are
		 * all ready.
		 */
		for (port = aggregator->lag_ports;
		     port;
		     port = port->next_port_in_aggregator) {
			if (!(port->sm_vars & AD_PORT_READY_N)) {
				retval = 0;
				break;
			}
		}
	}

	return retval;
}