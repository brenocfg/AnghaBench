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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct typec_altmode {int /*<<< orphan*/  mode; int /*<<< orphan*/  svid; } ;
struct pd_mode_data {size_t nsvids; size_t svid_index; int /*<<< orphan*/ * svids; } ;
struct tcpm_port {int nr_snk_vdo; int* snk_vdo; int /*<<< orphan*/  partner; int /*<<< orphan*/  data_role; int /*<<< orphan*/  partner_altmode; int /*<<< orphan*/  port_altmode; struct pd_mode_data mode_data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ALTMODE_DISCOVERY_MAX ; 
#define  CMDT_INIT 136 
#define  CMDT_RSP_ACK 135 
 int CMDT_RSP_BUSY ; 
#define  CMDT_RSP_NAK 134 
#define  CMD_ATTENTION 133 
#define  CMD_DISCOVER_IDENT 132 
#define  CMD_DISCOVER_MODES 131 
#define  CMD_DISCOVER_SVID 130 
#define  CMD_ENTER_MODE 129 
#define  CMD_EXIT_MODE 128 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PD_MAX_PAYLOAD ; 
 int PD_VDO_CMD (int) ; 
 int PD_VDO_CMDT (int) ; 
 int /*<<< orphan*/  PD_VDO_OPOS (int) ; 
 int /*<<< orphan*/  PD_VDO_VID (int) ; 
 int /*<<< orphan*/  TYPEC_DEVICE ; 
 int /*<<< orphan*/  TYPEC_STATE_USB ; 
 int /*<<< orphan*/  USB_SID_PD ; 
 int VDO (int /*<<< orphan*/ ,int,int const) ; 
 int VDO_CMDT (int) ; 
 int VDO_OPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  supports_modal (struct tcpm_port*) ; 
 int /*<<< orphan*/  svdm_consume_identity (struct tcpm_port*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  svdm_consume_modes (struct tcpm_port*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  svdm_consume_svids (struct tcpm_port*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  tcpm_register_partner_altmodes (struct tcpm_port*) ; 
 int /*<<< orphan*/  typec_altmode_attention (struct typec_altmode*,int) ; 
 int /*<<< orphan*/  typec_altmode_notify (struct typec_altmode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typec_altmode_update_active (struct typec_altmode*,int) ; 
 int /*<<< orphan*/  typec_altmode_vdm (struct typec_altmode*,int,int*,int) ; 
 struct typec_altmode* typec_match_altmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_pd_svdm(struct tcpm_port *port, const __le32 *payload, int cnt,
			u32 *response)
{
	struct typec_altmode *adev;
	struct typec_altmode *pdev;
	struct pd_mode_data *modep;
	u32 p[PD_MAX_PAYLOAD];
	int rlen = 0;
	int cmd_type;
	int cmd;
	int i;

	for (i = 0; i < cnt; i++)
		p[i] = le32_to_cpu(payload[i]);

	cmd_type = PD_VDO_CMDT(p[0]);
	cmd = PD_VDO_CMD(p[0]);

	tcpm_log(port, "Rx VDM cmd 0x%x type %d cmd %d len %d",
		 p[0], cmd_type, cmd, cnt);

	modep = &port->mode_data;

	adev = typec_match_altmode(port->port_altmode, ALTMODE_DISCOVERY_MAX,
				   PD_VDO_VID(p[0]), PD_VDO_OPOS(p[0]));

	pdev = typec_match_altmode(port->partner_altmode, ALTMODE_DISCOVERY_MAX,
				   PD_VDO_VID(p[0]), PD_VDO_OPOS(p[0]));

	switch (cmd_type) {
	case CMDT_INIT:
		switch (cmd) {
		case CMD_DISCOVER_IDENT:
			/* 6.4.4.3.1: Only respond as UFP (device) */
			if (port->data_role == TYPEC_DEVICE &&
			    port->nr_snk_vdo) {
				for (i = 0; i <  port->nr_snk_vdo; i++)
					response[i + 1] = port->snk_vdo[i];
				rlen = port->nr_snk_vdo + 1;
			}
			break;
		case CMD_DISCOVER_SVID:
			break;
		case CMD_DISCOVER_MODES:
			break;
		case CMD_ENTER_MODE:
			break;
		case CMD_EXIT_MODE:
			break;
		case CMD_ATTENTION:
			/* Attention command does not have response */
			if (adev)
				typec_altmode_attention(adev, p[1]);
			return 0;
		default:
			break;
		}
		if (rlen >= 1) {
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_ACK);
		} else if (rlen == 0) {
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_NAK);
			rlen = 1;
		} else {
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_BUSY);
			rlen = 1;
		}
		break;
	case CMDT_RSP_ACK:
		/* silently drop message if we are not connected */
		if (IS_ERR_OR_NULL(port->partner))
			break;

		switch (cmd) {
		case CMD_DISCOVER_IDENT:
			/* 6.4.4.3.1 */
			svdm_consume_identity(port, payload, cnt);
			response[0] = VDO(USB_SID_PD, 1, CMD_DISCOVER_SVID);
			rlen = 1;
			break;
		case CMD_DISCOVER_SVID:
			/* 6.4.4.3.2 */
			if (svdm_consume_svids(port, payload, cnt)) {
				response[0] = VDO(USB_SID_PD, 1,
						  CMD_DISCOVER_SVID);
				rlen = 1;
			} else if (modep->nsvids && supports_modal(port)) {
				response[0] = VDO(modep->svids[0], 1,
						  CMD_DISCOVER_MODES);
				rlen = 1;
			}
			break;
		case CMD_DISCOVER_MODES:
			/* 6.4.4.3.3 */
			svdm_consume_modes(port, payload, cnt);
			modep->svid_index++;
			if (modep->svid_index < modep->nsvids) {
				u16 svid = modep->svids[modep->svid_index];
				response[0] = VDO(svid, 1, CMD_DISCOVER_MODES);
				rlen = 1;
			} else {
				tcpm_register_partner_altmodes(port);
			}
			break;
		case CMD_ENTER_MODE:
			if (adev && pdev) {
				typec_altmode_update_active(pdev, true);

				if (typec_altmode_vdm(adev, p[0], &p[1], cnt)) {
					response[0] = VDO(adev->svid, 1,
							  CMD_EXIT_MODE);
					response[0] |= VDO_OPOS(adev->mode);
					return 1;
				}
			}
			return 0;
		case CMD_EXIT_MODE:
			if (adev && pdev) {
				typec_altmode_update_active(pdev, false);

				/* Back to USB Operation */
				WARN_ON(typec_altmode_notify(adev,
							     TYPEC_STATE_USB,
							     NULL));
			}
			break;
		default:
			break;
		}
		break;
	case CMDT_RSP_NAK:
		switch (cmd) {
		case CMD_ENTER_MODE:
			/* Back to USB Operation */
			if (adev)
				WARN_ON(typec_altmode_notify(adev,
							     TYPEC_STATE_USB,
							     NULL));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	/* Informing the alternate mode drivers about everything */
	if (adev)
		typec_altmode_vdm(adev, p[0], &p[1], cnt);

	return rlen;
}