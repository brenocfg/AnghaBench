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
struct fchs_s {int /*<<< orphan*/  s_id; } ;
struct fc_logi_s {int dummy; } ;
struct bfa_fcs_rport_s {int dummy; } ;
struct bfa_fcs_lport_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPSM_EVENT_PLOGI_COMP ; 
 int /*<<< orphan*/  WWN_NULL ; 
 struct bfa_fcs_rport_s* bfa_fcs_rport_alloc (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_rport_update (struct bfa_fcs_rport_s*,struct fc_logi_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_rport_start(struct bfa_fcs_lport_s *port, struct fchs_s *fchs,
	 struct fc_logi_s *plogi)
{
	struct bfa_fcs_rport_s *rport;

	rport = bfa_fcs_rport_alloc(port, WWN_NULL, fchs->s_id);
	if (!rport)
		return;

	bfa_fcs_rport_update(rport, plogi);

	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_COMP);
}