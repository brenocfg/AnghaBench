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
struct tcpm_port {scalar_t__ queued_message; scalar_t__ delayed_state; scalar_t__ delayed_runtime; int /*<<< orphan*/  state_machine; int /*<<< orphan*/  wq; } ;
typedef  enum pd_msg_request { ____Placeholder_pd_msg_request } pd_msg_request ;

/* Variables and functions */
 scalar_t__ INVALID_STATE ; 
 int /*<<< orphan*/  PD_CTRL_NOT_SUPP ; 
 int /*<<< orphan*/  PD_CTRL_REJECT ; 
 int /*<<< orphan*/  PD_CTRL_WAIT ; 
#define  PD_MSG_CTRL_NOT_SUPP 132 
#define  PD_MSG_CTRL_REJECT 131 
#define  PD_MSG_CTRL_WAIT 130 
#define  PD_MSG_DATA_SINK_CAP 129 
#define  PD_MSG_DATA_SOURCE_CAP 128 
 scalar_t__ PD_MSG_NONE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tcpm_pd_send_control (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_pd_send_sink_caps (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_pd_send_source_caps (struct tcpm_port*) ; 
 scalar_t__ time_is_after_jiffies (scalar_t__) ; 

__attribute__((used)) static bool tcpm_send_queued_message(struct tcpm_port *port)
{
	enum pd_msg_request queued_message;

	do {
		queued_message = port->queued_message;
		port->queued_message = PD_MSG_NONE;

		switch (queued_message) {
		case PD_MSG_CTRL_WAIT:
			tcpm_pd_send_control(port, PD_CTRL_WAIT);
			break;
		case PD_MSG_CTRL_REJECT:
			tcpm_pd_send_control(port, PD_CTRL_REJECT);
			break;
		case PD_MSG_CTRL_NOT_SUPP:
			tcpm_pd_send_control(port, PD_CTRL_NOT_SUPP);
			break;
		case PD_MSG_DATA_SINK_CAP:
			tcpm_pd_send_sink_caps(port);
			break;
		case PD_MSG_DATA_SOURCE_CAP:
			tcpm_pd_send_source_caps(port);
			break;
		default:
			break;
		}
	} while (port->queued_message != PD_MSG_NONE);

	if (port->delayed_state != INVALID_STATE) {
		if (time_is_after_jiffies(port->delayed_runtime)) {
			mod_delayed_work(port->wq, &port->state_machine,
					 port->delayed_runtime - jiffies);
			return true;
		}
		port->delayed_state = INVALID_STATE;
	}
	return false;
}