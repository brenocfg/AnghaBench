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
struct bfa_fcs_lport_scn_s {struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {int dummy; } ;

/* Variables and functions */
 struct bfa_fcs_lport_scn_s* BFA_FCS_GET_SCN_FROM_PORT (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  SCNSM_EVENT_PORT_ONLINE ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_scn_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_lport_fab_scn_online(struct bfa_fcs_lport_s *port)
{
	struct bfa_fcs_lport_scn_s *scn = BFA_FCS_GET_SCN_FROM_PORT(port);

	scn->port = port;
	bfa_sm_send_event(scn, SCNSM_EVENT_PORT_ONLINE);
}