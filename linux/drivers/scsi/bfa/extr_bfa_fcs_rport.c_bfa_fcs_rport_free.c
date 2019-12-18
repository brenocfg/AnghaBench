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
struct bfa_fcs_s {int /*<<< orphan*/  num_rport_logins; } ;
struct bfa_fcs_rport_s {scalar_t__ pid; int /*<<< orphan*/  rp_drv; int /*<<< orphan*/ * bfa_rport; int /*<<< orphan*/  itnim; int /*<<< orphan*/  plogi_pending; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {struct bfa_fcs_s* fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_FCS_PID_IS_WKA (scalar_t__) ; 
 int /*<<< orphan*/  BFA_RPORT_SM_DELETE ; 
 int /*<<< orphan*/  bfa_fcs_itnim_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_del_rport (struct bfa_fcs_lport_s*,struct bfa_fcs_rport_s*) ; 
 scalar_t__ bfa_fcs_lport_is_initiator (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rpf_rport_offline (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_free(struct bfa_fcs_rport_s *rport)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct bfa_fcs_s *fcs = port->fcs;

	/*
	 * - delete FC-4s
	 * - delete BFA rport
	 * - remove from queue of rports
	 */
	rport->plogi_pending = BFA_FALSE;

	if (bfa_fcs_lport_is_initiator(port)) {
		bfa_fcs_itnim_delete(rport->itnim);
		if (rport->pid != 0 && !BFA_FCS_PID_IS_WKA(rport->pid))
			bfa_fcs_rpf_rport_offline(rport);
	}

	if (rport->bfa_rport) {
		bfa_sm_send_event(rport->bfa_rport, BFA_RPORT_SM_DELETE);
		rport->bfa_rport = NULL;
	}

	bfa_fcs_lport_del_rport(port, rport);
	fcs->num_rport_logins--;
	kfree(rport->rp_drv);
}