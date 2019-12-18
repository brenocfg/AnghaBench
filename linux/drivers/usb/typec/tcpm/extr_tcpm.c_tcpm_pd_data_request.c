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
struct tcpm_port {unsigned int nr_source_caps; unsigned int negotiated_rev; unsigned int nr_sink_caps; void* bist_request; int /*<<< orphan*/  state; void** sink_caps; void* sink_request; int /*<<< orphan*/  pwr_role; void** source_caps; } ;
struct pd_message {int /*<<< orphan*/ * payload; int /*<<< orphan*/  header; } ;
typedef  enum pd_data_msg_type { ____Placeholder_pd_data_msg_type } pd_data_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  BIST_RX ; 
#define  PD_DATA_ALERT 135 
#define  PD_DATA_BATT_STATUS 134 
#define  PD_DATA_BIST 133 
#define  PD_DATA_GET_COUNTRY_INFO 132 
#define  PD_DATA_REQUEST 131 
#define  PD_DATA_SINK_CAP 130 
#define  PD_DATA_SOURCE_CAP 129 
#define  PD_DATA_VENDOR_DEF 128 
 unsigned int PD_MAX_REV ; 
 int /*<<< orphan*/  PD_MSG_CTRL_NOT_SUPP ; 
 int /*<<< orphan*/  PD_MSG_CTRL_REJECT ; 
 unsigned int PD_REV10 ; 
 int /*<<< orphan*/  SNK_NEGOTIATE_CAPABILITIES ; 
 int /*<<< orphan*/  SNK_READY ; 
 int /*<<< orphan*/  SRC_NEGOTIATE_CAPABILITIES ; 
 int /*<<< orphan*/  SRC_READY ; 
 int /*<<< orphan*/  TYPEC_SINK ; 
 int /*<<< orphan*/  TYPEC_SOURCE ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int pd_header_cnt_le (int /*<<< orphan*/ ) ; 
 unsigned int pd_header_rev_le (int /*<<< orphan*/ ) ; 
 int pd_header_type_le (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_handle_alert (struct tcpm_port*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tcpm_handle_vdm_request (struct tcpm_port*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int) ; 
 int /*<<< orphan*/  tcpm_log_source_caps (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_queue_message (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_validate_caps (struct tcpm_port*,void**,unsigned int) ; 

__attribute__((used)) static void tcpm_pd_data_request(struct tcpm_port *port,
				 const struct pd_message *msg)
{
	enum pd_data_msg_type type = pd_header_type_le(msg->header);
	unsigned int cnt = pd_header_cnt_le(msg->header);
	unsigned int rev = pd_header_rev_le(msg->header);
	unsigned int i;

	switch (type) {
	case PD_DATA_SOURCE_CAP:
		if (port->pwr_role != TYPEC_SINK)
			break;

		for (i = 0; i < cnt; i++)
			port->source_caps[i] = le32_to_cpu(msg->payload[i]);

		port->nr_source_caps = cnt;

		tcpm_log_source_caps(port);

		tcpm_validate_caps(port, port->source_caps,
				   port->nr_source_caps);

		/*
		 * Adjust revision in subsequent message headers, as required,
		 * to comply with 6.2.1.1.5 of the USB PD 3.0 spec. We don't
		 * support Rev 1.0 so just do nothing in that scenario.
		 */
		if (rev == PD_REV10)
			break;

		if (rev < PD_MAX_REV)
			port->negotiated_rev = rev;

		/*
		 * This message may be received even if VBUS is not
		 * present. This is quite unexpected; see USB PD
		 * specification, sections 8.3.3.6.3.1 and 8.3.3.6.3.2.
		 * However, at the same time, we must be ready to
		 * receive this message and respond to it 15ms after
		 * receiving PS_RDY during power swap operations, no matter
		 * if VBUS is available or not (USB PD specification,
		 * section 6.5.9.2).
		 * So we need to accept the message either way,
		 * but be prepared to keep waiting for VBUS after it was
		 * handled.
		 */
		tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
		break;
	case PD_DATA_REQUEST:
		if (port->pwr_role != TYPEC_SOURCE ||
		    cnt != 1) {
			tcpm_queue_message(port, PD_MSG_CTRL_REJECT);
			break;
		}

		/*
		 * Adjust revision in subsequent message headers, as required,
		 * to comply with 6.2.1.1.5 of the USB PD 3.0 spec. We don't
		 * support Rev 1.0 so just reject in that scenario.
		 */
		if (rev == PD_REV10) {
			tcpm_queue_message(port, PD_MSG_CTRL_REJECT);
			break;
		}

		if (rev < PD_MAX_REV)
			port->negotiated_rev = rev;

		port->sink_request = le32_to_cpu(msg->payload[0]);
		tcpm_set_state(port, SRC_NEGOTIATE_CAPABILITIES, 0);
		break;
	case PD_DATA_SINK_CAP:
		/* We don't do anything with this at the moment... */
		for (i = 0; i < cnt; i++)
			port->sink_caps[i] = le32_to_cpu(msg->payload[i]);
		port->nr_sink_caps = cnt;
		break;
	case PD_DATA_VENDOR_DEF:
		tcpm_handle_vdm_request(port, msg->payload, cnt);
		break;
	case PD_DATA_BIST:
		if (port->state == SRC_READY || port->state == SNK_READY) {
			port->bist_request = le32_to_cpu(msg->payload[0]);
			tcpm_set_state(port, BIST_RX, 0);
		}
		break;
	case PD_DATA_ALERT:
		tcpm_handle_alert(port, msg->payload, cnt);
		break;
	case PD_DATA_BATT_STATUS:
	case PD_DATA_GET_COUNTRY_INFO:
		/* Currently unsupported */
		tcpm_queue_message(port, PD_MSG_CTRL_NOT_SUPP);
		break;
	default:
		tcpm_log(port, "Unhandled data message type %#x", type);
		break;
	}
}