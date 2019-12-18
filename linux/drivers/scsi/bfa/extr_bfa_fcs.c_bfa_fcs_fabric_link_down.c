#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pwwn; } ;
struct TYPE_4__ {TYPE_1__ port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_2__ bport; int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_LINK_DOWN ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_fabric_link_down(struct bfa_fcs_fabric_s *fabric)
{
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_LINK_DOWN);
}