#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int port_state; } ;
struct port {scalar_t__ sm_mux_state; int sm_vars; int actor_oper_port_state; int ntt; TYPE_4__* aggregator; int /*<<< orphan*/  sm_mux_timer_counter; int /*<<< orphan*/  actor_port_number; TYPE_3__* slave; TYPE_1__ partner_oper; } ;
typedef  scalar_t__ mux_states_t ;
struct TYPE_9__ {int /*<<< orphan*/  is_active; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; TYPE_2__* bond; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AD_MUX_ATTACHED 131 
#define  AD_MUX_COLLECTING_DISTRIBUTING 130 
#define  AD_MUX_DETACHED 129 
#define  AD_MUX_WAITING 128 
 int AD_PORT_BEGIN ; 
 int AD_PORT_READY ; 
 int AD_PORT_READY_N ; 
 int AD_PORT_SELECTED ; 
 int AD_PORT_STANDBY ; 
 int AD_STATE_COLLECTING ; 
 int AD_STATE_DISTRIBUTING ; 
 int AD_STATE_SYNCHRONIZATION ; 
 int /*<<< orphan*/  AD_WAIT_WHILE_TIMER ; 
 int /*<<< orphan*/  __ad_timer_to_ticks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __agg_ports_are_ready (TYPE_4__*) ; 
 int /*<<< orphan*/  __check_agg_selection_timer (struct port*) ; 
 int /*<<< orphan*/  __enable_port (struct port*) ; 
 int /*<<< orphan*/  __port_is_enabled (struct port*) ; 
 int /*<<< orphan*/  __set_agg_ports_ready (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad_disable_collecting_distributing (struct port*,int*) ; 
 int /*<<< orphan*/  ad_enable_collecting_distributing (struct port*,int*) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ad_mux_machine(struct port *port, bool *update_slave_arr)
{
	mux_states_t last_state;

	/* keep current State Machine state to compare later if it was
	 * changed
	 */
	last_state = port->sm_mux_state;

	if (port->sm_vars & AD_PORT_BEGIN) {
		port->sm_mux_state = AD_MUX_DETACHED;
	} else {
		switch (port->sm_mux_state) {
		case AD_MUX_DETACHED:
			if ((port->sm_vars & AD_PORT_SELECTED)
			    || (port->sm_vars & AD_PORT_STANDBY))
				/* if SELECTED or STANDBY */
				port->sm_mux_state = AD_MUX_WAITING;
			break;
		case AD_MUX_WAITING:
			/* if SELECTED == FALSE return to DETACH state */
			if (!(port->sm_vars & AD_PORT_SELECTED)) {
				port->sm_vars &= ~AD_PORT_READY_N;
				/* in order to withhold the Selection Logic to
				 * check all ports READY_N value every callback
				 * cycle to update ready variable, we check
				 * READY_N and update READY here
				 */
				__set_agg_ports_ready(port->aggregator, __agg_ports_are_ready(port->aggregator));
				port->sm_mux_state = AD_MUX_DETACHED;
				break;
			}

			/* check if the wait_while_timer expired */
			if (port->sm_mux_timer_counter
			    && !(--port->sm_mux_timer_counter))
				port->sm_vars |= AD_PORT_READY_N;

			/* in order to withhold the selection logic to check
			 * all ports READY_N value every callback cycle to
			 * update ready variable, we check READY_N and update
			 * READY here
			 */
			__set_agg_ports_ready(port->aggregator, __agg_ports_are_ready(port->aggregator));

			/* if the wait_while_timer expired, and the port is
			 * in READY state, move to ATTACHED state
			 */
			if ((port->sm_vars & AD_PORT_READY)
			    && !port->sm_mux_timer_counter)
				port->sm_mux_state = AD_MUX_ATTACHED;
			break;
		case AD_MUX_ATTACHED:
			/* check also if agg_select_timer expired (so the
			 * edable port will take place only after this timer)
			 */
			if ((port->sm_vars & AD_PORT_SELECTED) &&
			    (port->partner_oper.port_state & AD_STATE_SYNCHRONIZATION) &&
			    !__check_agg_selection_timer(port)) {
				if (port->aggregator->is_active)
					port->sm_mux_state =
					    AD_MUX_COLLECTING_DISTRIBUTING;
			} else if (!(port->sm_vars & AD_PORT_SELECTED) ||
				   (port->sm_vars & AD_PORT_STANDBY)) {
				/* if UNSELECTED or STANDBY */
				port->sm_vars &= ~AD_PORT_READY_N;
				/* in order to withhold the selection logic to
				 * check all ports READY_N value every callback
				 * cycle to update ready variable, we check
				 * READY_N and update READY here
				 */
				__set_agg_ports_ready(port->aggregator, __agg_ports_are_ready(port->aggregator));
				port->sm_mux_state = AD_MUX_DETACHED;
			} else if (port->aggregator->is_active) {
				port->actor_oper_port_state |=
				    AD_STATE_SYNCHRONIZATION;
			}
			break;
		case AD_MUX_COLLECTING_DISTRIBUTING:
			if (!(port->sm_vars & AD_PORT_SELECTED) ||
			    (port->sm_vars & AD_PORT_STANDBY) ||
			    !(port->partner_oper.port_state & AD_STATE_SYNCHRONIZATION) ||
			    !(port->actor_oper_port_state & AD_STATE_SYNCHRONIZATION)) {
				port->sm_mux_state = AD_MUX_ATTACHED;
			} else {
				/* if port state hasn't changed make
				 * sure that a collecting distributing
				 * port in an active aggregator is enabled
				 */
				if (port->aggregator &&
				    port->aggregator->is_active &&
				    !__port_is_enabled(port)) {

					__enable_port(port);
				}
			}
			break;
		default:
			break;
		}
	}

	/* check if the state machine was changed */
	if (port->sm_mux_state != last_state) {
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Mux Machine: Port=%d, Last State=%d, Curr State=%d\n",
			  port->actor_port_number,
			  last_state,
			  port->sm_mux_state);
		switch (port->sm_mux_state) {
		case AD_MUX_DETACHED:
			port->actor_oper_port_state &= ~AD_STATE_SYNCHRONIZATION;
			ad_disable_collecting_distributing(port,
							   update_slave_arr);
			port->actor_oper_port_state &= ~AD_STATE_COLLECTING;
			port->actor_oper_port_state &= ~AD_STATE_DISTRIBUTING;
			port->ntt = true;
			break;
		case AD_MUX_WAITING:
			port->sm_mux_timer_counter = __ad_timer_to_ticks(AD_WAIT_WHILE_TIMER, 0);
			break;
		case AD_MUX_ATTACHED:
			if (port->aggregator->is_active)
				port->actor_oper_port_state |=
				    AD_STATE_SYNCHRONIZATION;
			else
				port->actor_oper_port_state &=
				    ~AD_STATE_SYNCHRONIZATION;
			port->actor_oper_port_state &= ~AD_STATE_COLLECTING;
			port->actor_oper_port_state &= ~AD_STATE_DISTRIBUTING;
			ad_disable_collecting_distributing(port,
							   update_slave_arr);
			port->ntt = true;
			break;
		case AD_MUX_COLLECTING_DISTRIBUTING:
			port->actor_oper_port_state |= AD_STATE_COLLECTING;
			port->actor_oper_port_state |= AD_STATE_DISTRIBUTING;
			port->actor_oper_port_state |= AD_STATE_SYNCHRONIZATION;
			ad_enable_collecting_distributing(port,
							  update_slave_arr);
			port->ntt = true;
			break;
		default:
			break;
		}
	}
}