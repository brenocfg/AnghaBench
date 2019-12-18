#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ port_id; int /*<<< orphan*/  port_name; } ;
struct TYPE_6__ {TYPE_2__ ids; } ;
struct fcoe_rport {int flags; int /*<<< orphan*/  enode_mac; TYPE_3__ rdata; } ;
struct fcoe_ctlr {scalar_t__ port_id; int state; TYPE_1__* lp; } ;
struct TYPE_4__ {int /*<<< orphan*/  wwpn; } ;

/* Variables and functions */
 int FIP_FL_REC_OR_P2P ; 
 int /*<<< orphan*/  FIP_SC_VN_PROBE_REP ; 
#define  FIP_ST_VNMP_CLAIM 132 
#define  FIP_ST_VNMP_PROBE1 131 
#define  FIP_ST_VNMP_PROBE2 130 
#define  FIP_ST_VNMP_START 129 
#define  FIP_ST_VNMP_UP 128 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,...) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_restart (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send (struct fcoe_ctlr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_ctlr_vn_probe_req(struct fcoe_ctlr *fip,
				   struct fcoe_rport *frport)
{
	if (frport->rdata.ids.port_id != fip->port_id)
		return;

	switch (fip->state) {
	case FIP_ST_VNMP_CLAIM:
	case FIP_ST_VNMP_UP:
		LIBFCOE_FIP_DBG(fip, "vn_probe_req: send reply, state %x\n",
				fip->state);
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REP,
				  frport->enode_mac, 0);
		break;
	case FIP_ST_VNMP_PROBE1:
	case FIP_ST_VNMP_PROBE2:
		/*
		 * Decide whether to reply to the Probe.
		 * Our selected address is never a "recorded" one, so
		 * only reply if our WWPN is greater and the
		 * Probe's REC bit is not set.
		 * If we don't reply, we will change our address.
		 */
		if (fip->lp->wwpn > frport->rdata.ids.port_name &&
		    !(frport->flags & FIP_FL_REC_OR_P2P)) {
			LIBFCOE_FIP_DBG(fip, "vn_probe_req: "
					"port_id collision\n");
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REP,
					  frport->enode_mac, 0);
			break;
		}
		/* fall through */
	case FIP_ST_VNMP_START:
		LIBFCOE_FIP_DBG(fip, "vn_probe_req: "
				"restart VN2VN negotiation\n");
		fcoe_ctlr_vn_restart(fip);
		break;
	default:
		LIBFCOE_FIP_DBG(fip, "vn_probe_req: ignore state %x\n",
				fip->state);
		break;
	}
}