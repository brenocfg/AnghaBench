#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ port_id; } ;
struct TYPE_4__ {TYPE_1__ ids; } ;
struct fcoe_rport {TYPE_2__ rdata; } ;
struct fcoe_ctlr {scalar_t__ port_id; int state; } ;

/* Variables and functions */
#define  FIP_ST_VNMP_CLAIM 132 
#define  FIP_ST_VNMP_PROBE1 131 
#define  FIP_ST_VNMP_PROBE2 130 
#define  FIP_ST_VNMP_START 129 
#define  FIP_ST_VNMP_UP 128 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,...) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_restart (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send_claim (struct fcoe_ctlr*) ; 

__attribute__((used)) static void fcoe_ctlr_vn_probe_reply(struct fcoe_ctlr *fip,
				     struct fcoe_rport *frport)
{
	if (frport->rdata.ids.port_id != fip->port_id)
		return;
	switch (fip->state) {
	case FIP_ST_VNMP_START:
	case FIP_ST_VNMP_PROBE1:
	case FIP_ST_VNMP_PROBE2:
	case FIP_ST_VNMP_CLAIM:
		LIBFCOE_FIP_DBG(fip, "vn_probe_reply: restart state %x\n",
				fip->state);
		fcoe_ctlr_vn_restart(fip);
		break;
	case FIP_ST_VNMP_UP:
		LIBFCOE_FIP_DBG(fip, "vn_probe_reply: send claim notify\n");
		fcoe_ctlr_vn_send_claim(fip);
		break;
	default:
		break;
	}
}