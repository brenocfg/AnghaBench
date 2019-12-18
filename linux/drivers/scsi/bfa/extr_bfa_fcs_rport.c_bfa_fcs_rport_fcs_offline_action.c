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
struct bfa_fcs_rport_s {int /*<<< orphan*/  itnim; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_PID_IS_WKA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_rport_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_rpf_rport_offline (struct bfa_fcs_rport_s*) ; 

__attribute__((used)) static void
bfa_fcs_rport_fcs_offline_action(struct bfa_fcs_rport_s *rport)
{
	if (!BFA_FCS_PID_IS_WKA(rport->pid))
		bfa_fcs_rpf_rport_offline(rport);

	bfa_fcs_itnim_rport_offline(rport->itnim);
}