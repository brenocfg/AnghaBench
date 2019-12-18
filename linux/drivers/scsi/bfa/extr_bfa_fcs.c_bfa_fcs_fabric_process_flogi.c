#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  s_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  bbcred; scalar_t__ port_type; } ;
struct fc_logi_s {int /*<<< orphan*/  port_name; TYPE_2__ csp; } ;
struct TYPE_7__ {int /*<<< orphan*/  reply_oxid; int /*<<< orphan*/  rem_port_wwn; } ;
struct TYPE_8__ {TYPE_3__ pn2n; } ;
struct bfa_fcs_lport_s {TYPE_4__ port_topo; } ;
struct TYPE_5__ {int /*<<< orphan*/  flogi_rejected; int /*<<< orphan*/  flogi_rcvd; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  bb_credit; TYPE_1__ stats; int /*<<< orphan*/  fcs; struct bfa_fcs_lport_s bport; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_NO_FABRIC ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_send_flogi_acc (struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_fabric_process_flogi(struct bfa_fcs_fabric_s *fabric,
			struct fchs_s *fchs, u16 len)
{
	struct fc_logi_s *flogi = (struct fc_logi_s *) (fchs + 1);
	struct bfa_fcs_lport_s *bport = &fabric->bport;

	bfa_trc(fabric->fcs, fchs->s_id);

	fabric->stats.flogi_rcvd++;
	/*
	 * Check port type. It should be 0 = n-port.
	 */
	if (flogi->csp.port_type) {
		/*
		 * @todo: may need to send a LS_RJT
		 */
		bfa_trc(fabric->fcs, flogi->port_name);
		fabric->stats.flogi_rejected++;
		return;
	}

	fabric->bb_credit = be16_to_cpu(flogi->csp.bbcred);
	bport->port_topo.pn2n.rem_port_wwn = flogi->port_name;
	bport->port_topo.pn2n.reply_oxid = fchs->ox_id;

	/*
	 * Send a Flogi Acc
	 */
	bfa_fcs_fabric_send_flogi_acc(fabric);
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_NO_FABRIC);
}