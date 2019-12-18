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
struct TYPE_2__ {int /*<<< orphan*/  offlines; } ;
struct bfa_fcs_itnim_s {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_OFFLINE ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_itnim_rport_offline(struct bfa_fcs_itnim_s *itnim)
{
	itnim->stats.offlines++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_OFFLINE);
}