#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int port_state; } ;
struct port {scalar_t__ sm_rx_state; int sm_vars; int actor_oper_port_key; int actor_oper_port_state; void* sm_rx_timer_counter; TYPE_4__* slave; int /*<<< orphan*/  actor_system; TYPE_1__ partner_oper; int /*<<< orphan*/  actor_port_number; scalar_t__ is_enabled; } ;
struct lacpdu {int /*<<< orphan*/  actor_system; } ;
typedef  scalar_t__ rx_states_t ;
struct TYPE_8__ {TYPE_3__* dev; TYPE_2__* bond; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_CURRENT_WHILE_TIMER ; 
 int AD_DUPLEX_KEY_MASKS ; 
 int AD_PORT_BEGIN ; 
 int AD_PORT_CHURNED ; 
 int AD_PORT_LACP_ENABLED ; 
 int AD_PORT_MATCHED ; 
 int AD_PORT_SELECTED ; 
#define  AD_RX_CURRENT 133 
#define  AD_RX_DEFAULTED 132 
#define  AD_RX_EXPIRED 131 
#define  AD_RX_INITIALIZE 130 
#define  AD_RX_LACP_DISABLED 129 
#define  AD_RX_PORT_DISABLED 128 
 int /*<<< orphan*/  AD_SHORT_TIMEOUT ; 
 int AD_STATE_AGGREGATION ; 
 int AD_STATE_EXPIRED ; 
 int AD_STATE_LACP_ACTIVITY ; 
 int AD_STATE_LACP_TIMEOUT ; 
 int AD_STATE_SYNCHRONIZATION ; 
 int /*<<< orphan*/  MAC_ADDRESS_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* __ad_timer_to_ticks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __record_default (struct port*) ; 
 int /*<<< orphan*/  __record_pdu (struct lacpdu*,struct port*) ; 
 int /*<<< orphan*/  __update_default_selected (struct port*) ; 
 int /*<<< orphan*/  __update_ntt (struct lacpdu*,struct port*) ; 
 int /*<<< orphan*/  __update_selected (struct lacpdu*,struct port*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ad_rx_machine(struct lacpdu *lacpdu, struct port *port)
{
	rx_states_t last_state;

	/* keep current State Machine state to compare later if it was
	 * changed
	 */
	last_state = port->sm_rx_state;

	/* check if state machine should change state */

	/* first, check if port was reinitialized */
	if (port->sm_vars & AD_PORT_BEGIN) {
		port->sm_rx_state = AD_RX_INITIALIZE;
		port->sm_vars |= AD_PORT_CHURNED;
	/* check if port is not enabled */
	} else if (!(port->sm_vars & AD_PORT_BEGIN) && !port->is_enabled)
		port->sm_rx_state = AD_RX_PORT_DISABLED;
	/* check if new lacpdu arrived */
	else if (lacpdu && ((port->sm_rx_state == AD_RX_EXPIRED) ||
		 (port->sm_rx_state == AD_RX_DEFAULTED) ||
		 (port->sm_rx_state == AD_RX_CURRENT))) {
		if (port->sm_rx_state != AD_RX_CURRENT)
			port->sm_vars |= AD_PORT_CHURNED;
		port->sm_rx_timer_counter = 0;
		port->sm_rx_state = AD_RX_CURRENT;
	} else {
		/* if timer is on, and if it is expired */
		if (port->sm_rx_timer_counter &&
		    !(--port->sm_rx_timer_counter)) {
			switch (port->sm_rx_state) {
			case AD_RX_EXPIRED:
				port->sm_rx_state = AD_RX_DEFAULTED;
				break;
			case AD_RX_CURRENT:
				port->sm_rx_state = AD_RX_EXPIRED;
				break;
			default:
				break;
			}
		} else {
			/* if no lacpdu arrived and no timer is on */
			switch (port->sm_rx_state) {
			case AD_RX_PORT_DISABLED:
				if (port->is_enabled &&
				    (port->sm_vars & AD_PORT_LACP_ENABLED))
					port->sm_rx_state = AD_RX_EXPIRED;
				else if (port->is_enabled
					 && ((port->sm_vars
					      & AD_PORT_LACP_ENABLED) == 0))
					port->sm_rx_state = AD_RX_LACP_DISABLED;
				break;
			default:
				break;

			}
		}
	}

	/* check if the State machine was changed or new lacpdu arrived */
	if ((port->sm_rx_state != last_state) || (lacpdu)) {
		pr_debug("Rx Machine: Port=%d (%s), Last State=%d, Curr State=%d\n",
			 port->actor_port_number,
			 port->slave->dev->name,
			 last_state,
			 port->sm_rx_state);
		switch (port->sm_rx_state) {
		case AD_RX_INITIALIZE:
			if (!(port->actor_oper_port_key & AD_DUPLEX_KEY_MASKS))
				port->sm_vars &= ~AD_PORT_LACP_ENABLED;
			else
				port->sm_vars |= AD_PORT_LACP_ENABLED;
			port->sm_vars &= ~AD_PORT_SELECTED;
			__record_default(port);
			port->actor_oper_port_state &= ~AD_STATE_EXPIRED;
			port->sm_rx_state = AD_RX_PORT_DISABLED;

			/* Fall Through */
		case AD_RX_PORT_DISABLED:
			port->sm_vars &= ~AD_PORT_MATCHED;
			break;
		case AD_RX_LACP_DISABLED:
			port->sm_vars &= ~AD_PORT_SELECTED;
			__record_default(port);
			port->partner_oper.port_state &= ~AD_STATE_AGGREGATION;
			port->sm_vars |= AD_PORT_MATCHED;
			port->actor_oper_port_state &= ~AD_STATE_EXPIRED;
			break;
		case AD_RX_EXPIRED:
			/* Reset of the Synchronization flag (Standard 43.4.12)
			 * This reset cause to disable this port in the
			 * COLLECTING_DISTRIBUTING state of the mux machine in
			 * case of EXPIRED even if LINK_DOWN didn't arrive for
			 * the port.
			 */
			port->partner_oper.port_state &= ~AD_STATE_SYNCHRONIZATION;
			port->sm_vars &= ~AD_PORT_MATCHED;
			port->partner_oper.port_state |= AD_STATE_LACP_TIMEOUT;
			port->partner_oper.port_state |= AD_STATE_LACP_ACTIVITY;
			port->sm_rx_timer_counter = __ad_timer_to_ticks(AD_CURRENT_WHILE_TIMER, (u16)(AD_SHORT_TIMEOUT));
			port->actor_oper_port_state |= AD_STATE_EXPIRED;
			port->sm_vars |= AD_PORT_CHURNED;
			break;
		case AD_RX_DEFAULTED:
			__update_default_selected(port);
			__record_default(port);
			port->sm_vars |= AD_PORT_MATCHED;
			port->actor_oper_port_state &= ~AD_STATE_EXPIRED;
			break;
		case AD_RX_CURRENT:
			/* detect loopback situation */
			if (MAC_ADDRESS_EQUAL(&(lacpdu->actor_system),
					      &(port->actor_system))) {
				netdev_err(port->slave->bond->dev, "An illegal loopback occurred on adapter (%s)\n"
				       "Check the configuration to verify that all adapters are connected to 802.3ad compliant switch ports\n",
				       port->slave->dev->name);
				return;
			}
			__update_selected(lacpdu, port);
			__update_ntt(lacpdu, port);
			__record_pdu(lacpdu, port);
			port->sm_rx_timer_counter = __ad_timer_to_ticks(AD_CURRENT_WHILE_TIMER, (u16)(port->actor_oper_port_state & AD_STATE_LACP_TIMEOUT));
			port->actor_oper_port_state &= ~AD_STATE_EXPIRED;
			break;
		default:
			break;
		}
	}
}