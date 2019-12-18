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
struct tcpm_port {int vbus_present; int vbus_never_low; int state; int /*<<< orphan*/  attached; int /*<<< orphan*/  pwr_role; } ;

/* Variables and functions */
#define  HARD_RESET_SEND 143 
#define  PORT_RESET_WAIT_OFF 142 
#define  PR_SWAP_SNK_SRC_SINK_OFF 141 
 int /*<<< orphan*/  PR_SWAP_SRC_SNK_SOURCE_OFF ; 
#define  PR_SWAP_SRC_SNK_TRANSITION_OFF 140 
#define  SNK_ATTACH_WAIT 139 
#define  SNK_HARD_RESET_SINK_OFF 138 
 int /*<<< orphan*/  SNK_HARD_RESET_WAIT_VBUS ; 
#define  SNK_NEGOTIATE_CAPABILITIES 137 
#define  SNK_TRY 136 
#define  SNK_TRYWAIT 135 
#define  SNK_TRYWAIT_DEBOUNCE 134 
#define  SNK_TRYWAIT_VBUS 133 
#define  SNK_TRY_WAIT_DEBOUNCE 132 
 int /*<<< orphan*/  SNK_UNATTACHED ; 
#define  SRC_HARD_RESET_VBUS_OFF 131 
 int /*<<< orphan*/  SRC_HARD_RESET_VBUS_ON ; 
#define  SRC_TRYWAIT 130 
 int /*<<< orphan*/  SRC_TRYWAIT_DEBOUNCE ; 
#define  SRC_TRY_DEBOUNCE 129 
#define  SRC_TRY_WAIT 128 
 int /*<<< orphan*/  TYPEC_SINK ; 
 int /*<<< orphan*/  tcpm_default_state (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*) ; 
 int /*<<< orphan*/  tcpm_port_is_source (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _tcpm_pd_vbus_off(struct tcpm_port *port)
{
	tcpm_log_force(port, "VBUS off");
	port->vbus_present = false;
	port->vbus_never_low = false;
	switch (port->state) {
	case SNK_HARD_RESET_SINK_OFF:
		tcpm_set_state(port, SNK_HARD_RESET_WAIT_VBUS, 0);
		break;
	case SRC_HARD_RESET_VBUS_OFF:
		tcpm_set_state(port, SRC_HARD_RESET_VBUS_ON, 0);
		break;
	case HARD_RESET_SEND:
		break;

	case SNK_TRY:
		/* Do nothing, waiting for timeout */
		break;
	case SRC_TRYWAIT:
		/* Hand over to state machine if needed */
		if (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT_DEBOUNCE, 0);
		break;
	case SNK_TRY_WAIT_DEBOUNCE:
		/* Do nothing, waiting for PD_DEBOUNCE to do be done */
		break;
	case SNK_TRYWAIT:
	case SNK_TRYWAIT_VBUS:
	case SNK_TRYWAIT_DEBOUNCE:
		break;
	case SNK_ATTACH_WAIT:
		tcpm_set_state(port, SNK_UNATTACHED, 0);
		break;

	case SNK_NEGOTIATE_CAPABILITIES:
		break;

	case PR_SWAP_SRC_SNK_TRANSITION_OFF:
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF, 0);
		break;

	case PR_SWAP_SNK_SRC_SINK_OFF:
		/* Do nothing, expected */
		break;

	case PORT_RESET_WAIT_OFF:
		tcpm_set_state(port, tcpm_default_state(port), 0);
		break;
	case SRC_TRY_WAIT:
	case SRC_TRY_DEBOUNCE:
		/* Do nothing, waiting for sink detection */
		break;
	default:
		if (port->pwr_role == TYPEC_SINK &&
		    port->attached)
			tcpm_set_state(port, SNK_UNATTACHED, 0);
		break;
	}
}