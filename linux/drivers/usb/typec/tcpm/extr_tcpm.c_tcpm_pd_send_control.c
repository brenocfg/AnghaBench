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
struct tcpm_port {int /*<<< orphan*/  message_id; int /*<<< orphan*/  negotiated_rev; int /*<<< orphan*/  data_role; int /*<<< orphan*/  pwr_role; } ;
struct pd_message {int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  enum pd_ctrl_msg_type { ____Placeholder_pd_ctrl_msg_type } pd_ctrl_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  PD_HEADER_LE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPC_TX_SOP ; 
 int /*<<< orphan*/  memset (struct pd_message*,int /*<<< orphan*/ ,int) ; 
 int tcpm_pd_transmit (struct tcpm_port*,int /*<<< orphan*/ ,struct pd_message*) ; 

__attribute__((used)) static int tcpm_pd_send_control(struct tcpm_port *port,
				enum pd_ctrl_msg_type type)
{
	struct pd_message msg;

	memset(&msg, 0, sizeof(msg));
	msg.header = PD_HEADER_LE(type, port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 0);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}