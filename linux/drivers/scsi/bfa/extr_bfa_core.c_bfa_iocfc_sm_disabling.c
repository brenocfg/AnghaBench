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
struct bfa_iocfc_s {int /*<<< orphan*/  bfa; } ;
typedef  enum iocfc_event { ____Placeholder_iocfc_event } iocfc_event ;

/* Variables and functions */
#define  IOCFC_E_CFG_DONE 131 
#define  IOCFC_E_DCONF_DONE 130 
#define  IOCFC_E_IOC_DISABLED 129 
#define  IOCFC_E_IOC_ENABLED 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocfc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_iocfc_sm_disabled ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_iocfc_sm_disabling(struct bfa_iocfc_s *iocfc, enum iocfc_event event)
{
	bfa_trc(iocfc->bfa, event);

	switch (event) {
	case IOCFC_E_IOC_DISABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabled);
		break;
	case IOCFC_E_IOC_ENABLED:
	case IOCFC_E_DCONF_DONE:
	case IOCFC_E_CFG_DONE:
		break;
	default:
		bfa_sm_fault(iocfc->bfa, event);
		break;
	}
}