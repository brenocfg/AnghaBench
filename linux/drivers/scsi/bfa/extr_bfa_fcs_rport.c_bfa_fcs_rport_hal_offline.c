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
struct bfa_fcs_rport_s {scalar_t__ bfa_rport; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_RPORT_SM_OFFLINE ; 
 int /*<<< orphan*/  bfa_cb_rport_offline (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_hal_offline(struct bfa_fcs_rport_s *rport)
{
	if (rport->bfa_rport)
		bfa_sm_send_event(rport->bfa_rport, BFA_RPORT_SM_OFFLINE);
	else
		bfa_cb_rport_offline(rport);
}