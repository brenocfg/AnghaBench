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
struct bfa_fcs_rport_s {int /*<<< orphan*/  scn_online; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  RPSM_EVENT_SCN_OFFLINE ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 

void
bfa_cb_rport_scn_no_dev(void *rport)
{
	struct bfa_fcs_rport_s *rp = rport;

	bfa_sm_send_event(rp, RPSM_EVENT_SCN_OFFLINE);
	rp->scn_online = BFA_FALSE;
}