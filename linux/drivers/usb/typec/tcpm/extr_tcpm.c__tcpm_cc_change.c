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
struct tcpm_port {int cc1; int cc2; size_t state; int delayed_state; int /*<<< orphan*/  max_wait; int /*<<< orphan*/  vbus_present; int /*<<< orphan*/  pd_capable; int /*<<< orphan*/  polarity; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;
typedef  enum tcpm_state { ____Placeholder_tcpm_state } tcpm_state ;

/* Variables and functions */
#define  ACC_UNATTACHED 157 
#define  AUDIO_ACC_ATTACHED 156 
#define  AUDIO_ACC_DEBOUNCE 155 
#define  DEBUG_ACC_ATTACHED 154 
#define  PR_SWAP_SNK_SRC_SINK_OFF 153 
#define  PR_SWAP_SNK_SRC_SOURCE_ON 152 
#define  PR_SWAP_SRC_SNK_SOURCE_OFF 151 
#define  PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED 150 
#define  PR_SWAP_SRC_SNK_TRANSITION_OFF 149 
 int SNK_ATTACHED ; 
#define  SNK_ATTACH_WAIT 148 
#define  SNK_DEBOUNCED 147 
#define  SNK_DISCOVERY 146 
#define  SNK_DISCOVERY_DEBOUNCE 145 
#define  SNK_READY 144 
#define  SNK_TRY 143 
#define  SNK_TRYWAIT 142 
#define  SNK_TRYWAIT_DEBOUNCE 141 
#define  SNK_TRYWAIT_VBUS 140 
#define  SNK_TRY_WAIT_DEBOUNCE 139 
#define  SNK_UNATTACHED 138 
#define  SRC_ATTACHED 137 
#define  SRC_ATTACH_WAIT 136 
#define  SRC_READY 135 
#define  SRC_SEND_CAPABILITIES 134 
 int SRC_TRY ; 
#define  SRC_TRYWAIT 133 
#define  SRC_TRYWAIT_DEBOUNCE 132 
#define  SRC_TRY_DEBOUNCE 131 
#define  SRC_TRY_WAIT 130 
#define  SRC_UNATTACHED 129 
#define  TOGGLING 128 
 int TYPEC_CC_OPEN ; 
 int /*<<< orphan*/  tcpm_get_current_limit (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tcpm_port_is_audio (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_port_is_audio_detached (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_port_is_debug (struct tcpm_port*) ; 
 scalar_t__ tcpm_port_is_disconnected (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_port_is_sink (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_port_is_source (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_set_current_limit (struct tcpm_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tcpm_states ; 
 int /*<<< orphan*/  tcpm_try_src (struct tcpm_port*) ; 
 int const unattached_state (struct tcpm_port*) ; 

__attribute__((used)) static void _tcpm_cc_change(struct tcpm_port *port, enum typec_cc_status cc1,
			    enum typec_cc_status cc2)
{
	enum typec_cc_status old_cc1, old_cc2;
	enum tcpm_state new_state;

	old_cc1 = port->cc1;
	old_cc2 = port->cc2;
	port->cc1 = cc1;
	port->cc2 = cc2;

	tcpm_log_force(port,
		       "CC1: %u -> %u, CC2: %u -> %u [state %s, polarity %d, %s]",
		       old_cc1, cc1, old_cc2, cc2, tcpm_states[port->state],
		       port->polarity,
		       tcpm_port_is_disconnected(port) ? "disconnected"
						       : "connected");

	switch (port->state) {
	case TOGGLING:
		if (tcpm_port_is_debug(port) || tcpm_port_is_audio(port) ||
		    tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		else if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		break;
	case SRC_UNATTACHED:
	case ACC_UNATTACHED:
		if (tcpm_port_is_debug(port) || tcpm_port_is_audio(port) ||
		    tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		break;
	case SRC_ATTACH_WAIT:
		if (tcpm_port_is_disconnected(port) ||
		    tcpm_port_is_audio_detached(port))
			tcpm_set_state(port, SRC_UNATTACHED, 0);
		else if (cc1 != old_cc1 || cc2 != old_cc2)
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		break;
	case SRC_ATTACHED:
	case SRC_SEND_CAPABILITIES:
	case SRC_READY:
		if (tcpm_port_is_disconnected(port) ||
		    !tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_UNATTACHED, 0);
		break;
	case SNK_UNATTACHED:
		if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		break;
	case SNK_ATTACH_WAIT:
		if ((port->cc1 == TYPEC_CC_OPEN &&
		     port->cc2 != TYPEC_CC_OPEN) ||
		    (port->cc1 != TYPEC_CC_OPEN &&
		     port->cc2 == TYPEC_CC_OPEN))
			new_state = SNK_DEBOUNCED;
		else if (tcpm_port_is_disconnected(port))
			new_state = SNK_UNATTACHED;
		else
			break;
		if (new_state != port->delayed_state)
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		break;
	case SNK_DEBOUNCED:
		if (tcpm_port_is_disconnected(port))
			new_state = SNK_UNATTACHED;
		else if (port->vbus_present)
			new_state = tcpm_try_src(port) ? SRC_TRY : SNK_ATTACHED;
		else
			new_state = SNK_UNATTACHED;
		if (new_state != port->delayed_state)
			tcpm_set_state(port, SNK_DEBOUNCED, 0);
		break;
	case SNK_READY:
		if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, unattached_state(port), 0);
		else if (!port->pd_capable &&
			 (cc1 != old_cc1 || cc2 != old_cc2))
			tcpm_set_current_limit(port,
					       tcpm_get_current_limit(port),
					       5000);
		break;

	case AUDIO_ACC_ATTACHED:
		if (cc1 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_OPEN)
			tcpm_set_state(port, AUDIO_ACC_DEBOUNCE, 0);
		break;
	case AUDIO_ACC_DEBOUNCE:
		if (tcpm_port_is_audio(port))
			tcpm_set_state(port, AUDIO_ACC_ATTACHED, 0);
		break;

	case DEBUG_ACC_ATTACHED:
		if (cc1 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_OPEN)
			tcpm_set_state(port, ACC_UNATTACHED, 0);
		break;

	case SNK_TRY:
		/* Do nothing, waiting for timeout */
		break;

	case SNK_DISCOVERY:
		/* CC line is unstable, wait for debounce */
		if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, SNK_DISCOVERY_DEBOUNCE, 0);
		break;
	case SNK_DISCOVERY_DEBOUNCE:
		break;

	case SRC_TRYWAIT:
		/* Hand over to state machine if needed */
		if (!port->vbus_present && tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT_DEBOUNCE, 0);
		break;
	case SRC_TRYWAIT_DEBOUNCE:
		if (port->vbus_present || !tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT, 0);
		break;
	case SNK_TRY_WAIT_DEBOUNCE:
		if (!tcpm_port_is_sink(port)) {
			port->max_wait = 0;
			tcpm_set_state(port, SRC_TRYWAIT, 0);
		}
		break;
	case SRC_TRY_WAIT:
		if (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRY_DEBOUNCE, 0);
		break;
	case SRC_TRY_DEBOUNCE:
		tcpm_set_state(port, SRC_TRY_WAIT, 0);
		break;
	case SNK_TRYWAIT_DEBOUNCE:
		if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_VBUS, 0);
		break;
	case SNK_TRYWAIT_VBUS:
		if (!tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_DEBOUNCE, 0);
		break;
	case SNK_TRYWAIT:
		/* Do nothing, waiting for tCCDebounce */
		break;
	case PR_SWAP_SNK_SRC_SINK_OFF:
	case PR_SWAP_SRC_SNK_TRANSITION_OFF:
	case PR_SWAP_SRC_SNK_SOURCE_OFF:
	case PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED:
	case PR_SWAP_SNK_SRC_SOURCE_ON:
		/*
		 * CC state change is expected in PR_SWAP
		 * Ignore it.
		 */
		break;

	default:
		if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, unattached_state(port), 0);
		break;
	}
}