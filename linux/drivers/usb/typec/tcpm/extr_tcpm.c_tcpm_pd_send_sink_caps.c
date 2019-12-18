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
struct tcpm_port {int nr_snk_pdo; int /*<<< orphan*/ * snk_pdo; int /*<<< orphan*/  message_id; int /*<<< orphan*/  negotiated_rev; int /*<<< orphan*/  data_role; int /*<<< orphan*/  pwr_role; } ;
struct pd_message {int /*<<< orphan*/ * payload; void* header; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  PD_CTRL_REJECT ; 
 int /*<<< orphan*/  PD_DATA_SINK_CAP ; 
 void* PD_HEADER_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCPC_TX_SOP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pd_message*,int /*<<< orphan*/ ,int) ; 
 int tcpm_pd_transmit (struct tcpm_port*,int /*<<< orphan*/ ,struct pd_message*) ; 

__attribute__((used)) static int tcpm_pd_send_sink_caps(struct tcpm_port *port)
{
	struct pd_message msg;
	int i;

	memset(&msg, 0, sizeof(msg));
	if (!port->nr_snk_pdo) {
		/* No sink capabilities defined, source only */
		msg.header = PD_HEADER_LE(PD_CTRL_REJECT,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, 0);
	} else {
		msg.header = PD_HEADER_LE(PD_DATA_SINK_CAP,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id,
					  port->nr_snk_pdo);
	}
	for (i = 0; i < port->nr_snk_pdo; i++)
		msg.payload[i] = cpu_to_le32(port->snk_pdo[i]);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}