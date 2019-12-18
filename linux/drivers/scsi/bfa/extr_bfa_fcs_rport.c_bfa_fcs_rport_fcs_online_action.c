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
struct bfa_fcs_rport_s {int /*<<< orphan*/  itnim; int /*<<< orphan*/  pid; int /*<<< orphan*/  fcs; int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_FCS_ONLINE ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_fcs_online_action(struct bfa_fcs_rport_s *rport)
{
	if ((!rport->pid) || (!rport->pwwn)) {
		bfa_trc(rport->fcs, rport->pid);
		bfa_sm_fault(rport->fcs, rport->pid);
	}

	bfa_sm_send_event(rport->itnim, BFA_FCS_ITNIM_SM_FCS_ONLINE);
}