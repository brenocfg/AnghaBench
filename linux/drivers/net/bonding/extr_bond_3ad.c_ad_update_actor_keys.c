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
typedef  int u8 ;
typedef  int u16 ;
struct port {int actor_oper_port_key; int actor_admin_port_key; int /*<<< orphan*/  sm_vars; int /*<<< orphan*/  actor_port_number; TYPE_2__* slave; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* bond; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AD_DUPLEX_KEY_MASKS ; 
 int /*<<< orphan*/  AD_PORT_BEGIN ; 
 int /*<<< orphan*/  AD_PORT_LACP_ENABLED ; 
 int AD_SPEED_KEY_MASKS ; 
 int __get_duplex (struct port*) ; 
 int __get_link_speed (struct port*) ; 
 int /*<<< orphan*/  slave_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_update_actor_keys(struct port *port, bool reset)
{
	u8 duplex = 0;
	u16 ospeed = 0, speed = 0;
	u16 old_oper_key = port->actor_oper_port_key;

	port->actor_admin_port_key &= ~(AD_SPEED_KEY_MASKS|AD_DUPLEX_KEY_MASKS);
	if (!reset) {
		speed = __get_link_speed(port);
		ospeed = (old_oper_key & AD_SPEED_KEY_MASKS) >> 1;
		duplex = __get_duplex(port);
		port->actor_admin_port_key |= (speed << 1) | duplex;
	}
	port->actor_oper_port_key = port->actor_admin_port_key;

	if (old_oper_key != port->actor_oper_port_key) {
		/* Only 'duplex' port participates in LACP */
		if (duplex)
			port->sm_vars |= AD_PORT_LACP_ENABLED;
		else
			port->sm_vars &= ~AD_PORT_LACP_ENABLED;

		if (!reset) {
			if (!speed) {
				slave_err(port->slave->bond->dev,
					  port->slave->dev,
					  "speed changed to 0 on port %d\n",
					  port->actor_port_number);
			} else if (duplex && ospeed != speed) {
				/* Speed change restarts LACP state-machine */
				port->sm_vars |= AD_PORT_BEGIN;
			}
		}
	}
}