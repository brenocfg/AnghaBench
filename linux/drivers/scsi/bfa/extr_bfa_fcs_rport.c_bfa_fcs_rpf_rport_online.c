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
struct bfa_fcs_rport_s {int /*<<< orphan*/  rpf; TYPE_1__* port; int /*<<< orphan*/  pid; int /*<<< orphan*/  fcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fabric; int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPFSM_EVENT_RPORT_ONLINE ; 
 scalar_t__ __fcs_min_cfg (int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_fcs_fabric_is_switched (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_rpf_rport_online(struct bfa_fcs_rport_s *rport)
{
	bfa_trc(rport->fcs, rport->pid);

	if (__fcs_min_cfg(rport->port->fcs))
		return;

	if (bfa_fcs_fabric_is_switched(rport->port->fabric))
		bfa_sm_send_event(&rport->rpf, RPFSM_EVENT_RPORT_ONLINE);
}