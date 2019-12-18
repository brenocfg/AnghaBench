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
struct TYPE_2__ {int port_state; } ;
struct port {int sm_vars; scalar_t__ sm_churn_actor_state; scalar_t__ sm_churn_partner_state; int actor_oper_port_state; int /*<<< orphan*/  churn_partner_count; TYPE_1__ partner_oper; void* sm_churn_partner_timer_counter; int /*<<< orphan*/  churn_actor_count; void* sm_churn_actor_timer_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_ACTOR_CHURN_TIMER ; 
 void* AD_CHURN ; 
 scalar_t__ AD_CHURN_MONITOR ; 
 void* AD_NO_CHURN ; 
 int /*<<< orphan*/  AD_PARTNER_CHURN_TIMER ; 
 int AD_PORT_CHURNED ; 
 int AD_STATE_SYNCHRONIZATION ; 
 void* __ad_timer_to_ticks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_churn_machine(struct port *port)
{
	if (port->sm_vars & AD_PORT_CHURNED) {
		port->sm_vars &= ~AD_PORT_CHURNED;
		port->sm_churn_actor_state = AD_CHURN_MONITOR;
		port->sm_churn_partner_state = AD_CHURN_MONITOR;
		port->sm_churn_actor_timer_counter =
			__ad_timer_to_ticks(AD_ACTOR_CHURN_TIMER, 0);
		port->sm_churn_partner_timer_counter =
			 __ad_timer_to_ticks(AD_PARTNER_CHURN_TIMER, 0);
		return;
	}
	if (port->sm_churn_actor_timer_counter &&
	    !(--port->sm_churn_actor_timer_counter) &&
	    port->sm_churn_actor_state == AD_CHURN_MONITOR) {
		if (port->actor_oper_port_state & AD_STATE_SYNCHRONIZATION) {
			port->sm_churn_actor_state = AD_NO_CHURN;
		} else {
			port->churn_actor_count++;
			port->sm_churn_actor_state = AD_CHURN;
		}
	}
	if (port->sm_churn_partner_timer_counter &&
	    !(--port->sm_churn_partner_timer_counter) &&
	    port->sm_churn_partner_state == AD_CHURN_MONITOR) {
		if (port->partner_oper.port_state & AD_STATE_SYNCHRONIZATION) {
			port->sm_churn_partner_state = AD_NO_CHURN;
		} else {
			port->churn_partner_count++;
			port->sm_churn_partner_state = AD_CHURN;
		}
	}
}