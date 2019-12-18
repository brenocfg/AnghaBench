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
struct port {int /*<<< orphan*/  sm_vars; struct port_params partner_oper; } ;
struct lacpdu {int actor_state; int /*<<< orphan*/  actor_key; int /*<<< orphan*/  actor_system_priority; int /*<<< orphan*/  actor_system; int /*<<< orphan*/  actor_port_priority; int /*<<< orphan*/  actor_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_PORT_SELECTED ; 
 int AD_STATE_AGGREGATION ; 
 int /*<<< orphan*/  MAC_ADDRESS_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __update_selected(struct lacpdu *lacpdu, struct port *port)
{
	if (lacpdu && port) {
		const struct port_params *partner = &port->partner_oper;

		/* check if any parameter is different then
		 * update the state machine selected variable.
		 */
		if (ntohs(lacpdu->actor_port) != partner->port_number ||
		    ntohs(lacpdu->actor_port_priority) != partner->port_priority ||
		    !MAC_ADDRESS_EQUAL(&lacpdu->actor_system, &partner->system) ||
		    ntohs(lacpdu->actor_system_priority) != partner->system_priority ||
		    ntohs(lacpdu->actor_key) != partner->key ||
		    (lacpdu->actor_state & AD_STATE_AGGREGATION) != (partner->port_state & AD_STATE_AGGREGATION)) {
			port->sm_vars &= ~AD_PORT_SELECTED;
		}
	}
}