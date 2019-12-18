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
struct port_params {int /*<<< orphan*/  port_state; int /*<<< orphan*/  port_number; int /*<<< orphan*/  port_priority; int /*<<< orphan*/  key; int /*<<< orphan*/  system; int /*<<< orphan*/  system_priority; } ;
struct lacpdu {int /*<<< orphan*/  partner_state; void* partner_port; void* partner_port_priority; void* partner_key; int /*<<< orphan*/  partner_system; void* partner_system_priority; int /*<<< orphan*/  actor_state; void* actor_port; void* actor_port_priority; void* actor_key; int /*<<< orphan*/  actor_system; void* actor_system_priority; } ;
struct port {int /*<<< orphan*/  actor_oper_port_state; TYPE_2__* slave; int /*<<< orphan*/  actor_port_number; int /*<<< orphan*/  actor_port_priority; int /*<<< orphan*/  actor_oper_port_key; int /*<<< orphan*/  actor_system; int /*<<< orphan*/  actor_system_priority; struct port_params partner_oper; struct lacpdu lacpdu; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* bond; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __update_lacpdu_from_port(struct port *port)
{
	struct lacpdu *lacpdu = &port->lacpdu;
	const struct port_params *partner = &port->partner_oper;

	/* update current actual Actor parameters
	 * lacpdu->subtype                   initialized
	 * lacpdu->version_number            initialized
	 * lacpdu->tlv_type_actor_info       initialized
	 * lacpdu->actor_information_length  initialized
	 */

	lacpdu->actor_system_priority = htons(port->actor_system_priority);
	lacpdu->actor_system = port->actor_system;
	lacpdu->actor_key = htons(port->actor_oper_port_key);
	lacpdu->actor_port_priority = htons(port->actor_port_priority);
	lacpdu->actor_port = htons(port->actor_port_number);
	lacpdu->actor_state = port->actor_oper_port_state;
	slave_dbg(port->slave->bond->dev, port->slave->dev,
		  "update lacpdu: actor port state %x\n",
		  port->actor_oper_port_state);

	/* lacpdu->reserved_3_1              initialized
	 * lacpdu->tlv_type_partner_info     initialized
	 * lacpdu->partner_information_length initialized
	 */

	lacpdu->partner_system_priority = htons(partner->system_priority);
	lacpdu->partner_system = partner->system;
	lacpdu->partner_key = htons(partner->key);
	lacpdu->partner_port_priority = htons(partner->port_priority);
	lacpdu->partner_port = htons(partner->port_number);
	lacpdu->partner_state = partner->port_state;

	/* lacpdu->reserved_3_2              initialized
	 * lacpdu->tlv_type_collector_info   initialized
	 * lacpdu->collector_information_length initialized
	 * collector_max_delay                initialized
	 * reserved_12[12]                   initialized
	 * tlv_type_terminator               initialized
	 * terminator_length                 initialized
	 * reserved_50[50]                   initialized
	 */
}