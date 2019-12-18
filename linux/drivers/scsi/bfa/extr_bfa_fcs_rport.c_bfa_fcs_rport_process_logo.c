#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int /*<<< orphan*/  ox_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  logo_rcvd; } ;
struct bfa_fcs_rport_s {TYPE_1__ stats; int /*<<< orphan*/  prlo; int /*<<< orphan*/  reply_oxid; int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  RPSM_EVENT_LOGO_RCVD ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_process_logo(struct bfa_fcs_rport_s *rport, struct fchs_s *fchs)
{
	rport->reply_oxid = fchs->ox_id;
	bfa_trc(rport->fcs, rport->reply_oxid);

	rport->prlo = BFA_FALSE;
	rport->stats.logo_rcvd++;
	bfa_sm_send_event(rport, RPSM_EVENT_LOGO_RCVD);
}