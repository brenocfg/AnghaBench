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
struct TYPE_3__ {int /*<<< orphan*/  onlines; } ;
struct bfa_fcs_itnim_s {TYPE_2__* rport; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_HAL_ONLINE ; 
 int /*<<< orphan*/  BFA_FCS_PID_IS_WKA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_itnim_brp_online(struct bfa_fcs_itnim_s *itnim)
{
	itnim->stats.onlines++;

	if (!BFA_FCS_PID_IS_WKA(itnim->rport->pid))
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HAL_ONLINE);
}