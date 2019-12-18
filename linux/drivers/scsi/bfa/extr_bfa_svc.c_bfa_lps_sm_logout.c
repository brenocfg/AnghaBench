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
struct bfa_lps_s {int bfa_tag; int /*<<< orphan*/  bfa; } ;
typedef  enum bfa_lps_event { ____Placeholder_bfa_lps_event } bfa_lps_event ;

/* Variables and functions */
#define  BFA_LPS_SM_DELETE 130 
#define  BFA_LPS_SM_FWRSP 129 
#define  BFA_LPS_SM_OFFLINE 128 
 int /*<<< orphan*/  bfa_lps_logout_comp (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_sm_init ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_lps_sm_logout(struct bfa_lps_s *lps, enum bfa_lps_event event)
{
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	switch (event) {
	case BFA_LPS_SM_FWRSP:
	case BFA_LPS_SM_OFFLINE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_lps_logout_comp(lps);
		break;

	case BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		break;

	default:
		bfa_sm_fault(lps->bfa, event);
	}
}