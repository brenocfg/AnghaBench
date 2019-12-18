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
struct tcpm_port {int vdm_state; int vdo_count; int vdm_retries; int /*<<< orphan*/  vdo_retry; int /*<<< orphan*/ * vdo_data; int /*<<< orphan*/  vdm_state_machine; int /*<<< orphan*/  wq; int /*<<< orphan*/  message_id; int /*<<< orphan*/  negotiated_rev; int /*<<< orphan*/  data_role; int /*<<< orphan*/  pwr_role; int /*<<< orphan*/  state; int /*<<< orphan*/  attached; } ;
struct pd_message {int /*<<< orphan*/ * payload; int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  PD_DATA_VENDOR_DEF ; 
 int /*<<< orphan*/  PD_HEADER_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SNK_READY ; 
 int /*<<< orphan*/  SRC_READY ; 
 int /*<<< orphan*/  TCPC_TX_SOP ; 
#define  VDM_STATE_BUSY 131 
 int VDM_STATE_ERR_BUSY ; 
#define  VDM_STATE_ERR_SEND 130 
 int VDM_STATE_ERR_TMOUT ; 
#define  VDM_STATE_READY 129 
#define  VDM_STATE_WAIT_RSP_BUSY 128 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pd_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*) ; 
 int tcpm_pd_transmit (struct tcpm_port*,int /*<<< orphan*/ ,struct pd_message*) ; 
 unsigned long vdm_ready_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdm_run_state_machine(struct tcpm_port *port)
{
	struct pd_message msg;
	int i, res;

	switch (port->vdm_state) {
	case VDM_STATE_READY:
		/* Only transmit VDM if attached */
		if (!port->attached) {
			port->vdm_state = VDM_STATE_ERR_BUSY;
			break;
		}

		/*
		 * if there's traffic or we're not in PDO ready state don't send
		 * a VDM.
		 */
		if (port->state != SRC_READY && port->state != SNK_READY)
			break;

		/* Prepare and send VDM */
		memset(&msg, 0, sizeof(msg));
		msg.header = PD_HEADER_LE(PD_DATA_VENDOR_DEF,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, port->vdo_count);
		for (i = 0; i < port->vdo_count; i++)
			msg.payload[i] = cpu_to_le32(port->vdo_data[i]);
		res = tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
		if (res < 0) {
			port->vdm_state = VDM_STATE_ERR_SEND;
		} else {
			unsigned long timeout;

			port->vdm_retries = 0;
			port->vdm_state = VDM_STATE_BUSY;
			timeout = vdm_ready_timeout(port->vdo_data[0]);
			mod_delayed_work(port->wq, &port->vdm_state_machine,
					 timeout);
		}
		break;
	case VDM_STATE_WAIT_RSP_BUSY:
		port->vdo_data[0] = port->vdo_retry;
		port->vdo_count = 1;
		port->vdm_state = VDM_STATE_READY;
		break;
	case VDM_STATE_BUSY:
		port->vdm_state = VDM_STATE_ERR_TMOUT;
		break;
	case VDM_STATE_ERR_SEND:
		/*
		 * A partner which does not support USB PD will not reply,
		 * so this is not a fatal error. At the same time, some
		 * devices may not return GoodCRC under some circumstances,
		 * so we need to retry.
		 */
		if (port->vdm_retries < 3) {
			tcpm_log(port, "VDM Tx error, retry");
			port->vdm_retries++;
			port->vdm_state = VDM_STATE_READY;
		}
		break;
	default:
		break;
	}
}