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
struct port_params {scalar_t__ port_number; scalar_t__ port_priority; scalar_t__ system_priority; scalar_t__ key; int port_state; int /*<<< orphan*/  system; } ;
struct port {int /*<<< orphan*/  sm_vars; struct port_params partner_oper; struct port_params partner_admin; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_PORT_SELECTED ; 
 int AD_STATE_AGGREGATION ; 
 int /*<<< orphan*/  MAC_ADDRESS_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __update_default_selected(struct port *port)
{
	if (port) {
		const struct port_params *admin = &port->partner_admin;
		const struct port_params *oper = &port->partner_oper;

		/* check if any parameter is different then
		 * update the state machine selected variable.
		 */
		if (admin->port_number != oper->port_number ||
		    admin->port_priority != oper->port_priority ||
		    !MAC_ADDRESS_EQUAL(&admin->system, &oper->system) ||
		    admin->system_priority != oper->system_priority ||
		    admin->key != oper->key ||
		    (admin->port_state & AD_STATE_AGGREGATION)
			!= (oper->port_state & AD_STATE_AGGREGATION)) {
			port->sm_vars &= ~AD_PORT_SELECTED;
		}
	}
}