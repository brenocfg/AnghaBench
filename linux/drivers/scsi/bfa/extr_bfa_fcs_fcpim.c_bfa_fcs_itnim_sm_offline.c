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
struct bfa_fcs_itnim_s {int /*<<< orphan*/  fcs; TYPE_1__* rport; int /*<<< orphan*/  prli_retries; } ;
typedef  enum bfa_fcs_itnim_event { ____Placeholder_bfa_fcs_itnim_event } bfa_fcs_itnim_event ;
struct TYPE_2__ {int pwwn; } ;

/* Variables and functions */
#define  BFA_FCS_ITNIM_SM_DELETE 131 
#define  BFA_FCS_ITNIM_SM_FCS_ONLINE 130 
#define  BFA_FCS_ITNIM_SM_INITIATOR 129 
#define  BFA_FCS_ITNIM_SM_OFFLINE 128 
 int /*<<< orphan*/  RPSM_EVENT_FC4_OFFLINE ; 
 int /*<<< orphan*/  bfa_fcs_itnim_free (struct bfa_fcs_itnim_s*) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_send_prli (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_initiator ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_prli_send ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_itnim_sm_offline(struct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_FCS_ONLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_prli_send);
		itnim->prli_retries = 0;
		bfa_fcs_itnim_send_prli(itnim, NULL);
		break;

	case BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		break;

	case BFA_FCS_ITNIM_SM_INITIATOR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		break;

	case BFA_FCS_ITNIM_SM_DELETE:
		bfa_fcs_itnim_free(itnim);
		break;

	default:
		bfa_sm_fault(itnim->fcs, event);
	}

}