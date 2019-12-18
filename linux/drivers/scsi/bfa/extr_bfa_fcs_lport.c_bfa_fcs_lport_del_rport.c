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
struct bfa_fcs_rport_s {int /*<<< orphan*/  qe; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  num_rports; int /*<<< orphan*/  rport_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_PORT_SM_DELRPORT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
bfa_fcs_lport_del_rport(
	struct bfa_fcs_lport_s *port,
	struct bfa_fcs_rport_s *rport)
{
	WARN_ON(!bfa_q_is_on_q(&port->rport_q, rport));
	list_del(&rport->qe);
	port->num_rports--;

	bfa_sm_send_event(port, BFA_FCS_PORT_SM_DELRPORT);
}