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
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_fcs_lport_ms_s {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
 struct bfa_fcs_lport_ms_s* BFA_FCS_GET_MS_FROM_PORT (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  MSSM_EVENT_PORT_ONLINE ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_lport_ms_online(struct bfa_fcs_lport_s *port)
{
	struct bfa_fcs_lport_ms_s *ms = BFA_FCS_GET_MS_FROM_PORT(port);

	ms->port = port;
	bfa_sm_send_event(ms, MSSM_EVENT_PORT_ONLINE);
}