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
typedef  int /*<<< orphan*/  u32 ;
struct tcpm_port {int /*<<< orphan*/  message_id; int /*<<< orphan*/  negotiated_rev; int /*<<< orphan*/  data_role; int /*<<< orphan*/  pwr_role; } ;
struct pd_message {int /*<<< orphan*/ * payload; int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  PD_DATA_REQUEST ; 
 int /*<<< orphan*/  PD_HEADER_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCPC_TX_SOP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pd_message*,int /*<<< orphan*/ ,int) ; 
 int tcpm_pd_build_request (struct tcpm_port*,int /*<<< orphan*/ *) ; 
 int tcpm_pd_transmit (struct tcpm_port*,int /*<<< orphan*/ ,struct pd_message*) ; 

__attribute__((used)) static int tcpm_pd_send_request(struct tcpm_port *port)
{
	struct pd_message msg;
	int ret;
	u32 rdo;

	ret = tcpm_pd_build_request(port, &rdo);
	if (ret < 0)
		return ret;

	memset(&msg, 0, sizeof(msg));
	msg.header = PD_HEADER_LE(PD_DATA_REQUEST,
				  port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 1);
	msg.payload[0] = cpu_to_le32(rdo);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}