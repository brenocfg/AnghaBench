#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct port_params {int port_state; void* key; void* system_priority; int /*<<< orphan*/  system; void* port_priority; void* port_number; } ;
struct port {int sm_vars; TYPE_2__* slave; int /*<<< orphan*/  actor_oper_port_state; struct port_params partner_oper; } ;
struct lacpdu {int actor_state; int /*<<< orphan*/  actor_key; int /*<<< orphan*/  actor_system_priority; int /*<<< orphan*/  actor_system; int /*<<< orphan*/  actor_port_priority; int /*<<< orphan*/  actor_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* bond; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AD_PORT_MATCHED ; 
 int /*<<< orphan*/  AD_STATE_DEFAULTED ; 
 int AD_STATE_SYNCHRONIZATION ; 
 int /*<<< orphan*/  __choose_matched (struct lacpdu*,struct port*) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __record_pdu(struct lacpdu *lacpdu, struct port *port)
{
	if (lacpdu && port) {
		struct port_params *partner = &port->partner_oper;

		__choose_matched(lacpdu, port);
		/* record the new parameter values for the partner
		 * operational
		 */
		partner->port_number = ntohs(lacpdu->actor_port);
		partner->port_priority = ntohs(lacpdu->actor_port_priority);
		partner->system = lacpdu->actor_system;
		partner->system_priority = ntohs(lacpdu->actor_system_priority);
		partner->key = ntohs(lacpdu->actor_key);
		partner->port_state = lacpdu->actor_state;

		/* set actor_oper_port_state.defaulted to FALSE */
		port->actor_oper_port_state &= ~AD_STATE_DEFAULTED;

		/* set the partner sync. to on if the partner is sync,
		 * and the port is matched
		 */
		if ((port->sm_vars & AD_PORT_MATCHED) &&
		    (lacpdu->actor_state & AD_STATE_SYNCHRONIZATION)) {
			partner->port_state |= AD_STATE_SYNCHRONIZATION;
			slave_dbg(port->slave->bond->dev, port->slave->dev,
				  "partner sync=1\n");
		} else {
			partner->port_state &= ~AD_STATE_SYNCHRONIZATION;
			slave_dbg(port->slave->bond->dev, port->slave->dev,
				  "partner sync=0\n");
		}
	}
}