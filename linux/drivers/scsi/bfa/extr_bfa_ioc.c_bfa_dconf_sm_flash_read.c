#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_dconf_mod_s {TYPE_1__* bfa; int /*<<< orphan*/  timer; } ;
typedef  enum bfa_dconf_event { ____Placeholder_bfa_dconf_event } bfa_dconf_event ;
struct TYPE_3__ {int /*<<< orphan*/  iocfc; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
#define  BFA_DCONF_SM_EXIT 131 
#define  BFA_DCONF_SM_FLASH_COMP 130 
#define  BFA_DCONF_SM_IOCDISABLE 129 
#define  BFA_DCONF_SM_TIMEOUT 128 
 int /*<<< orphan*/  IOCFC_E_DCONF_DONE ; 
 int /*<<< orphan*/  bfa_dconf_sm_ready ; 
 int /*<<< orphan*/  bfa_dconf_sm_uninit ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dconf_mod_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_dconf_sm_flash_read(struct bfa_dconf_mod_s *dconf,
			enum bfa_dconf_event event)
{
	bfa_trc(dconf->bfa, event);

	switch (event) {
	case BFA_DCONF_SM_FLASH_COMP:
		bfa_timer_stop(&dconf->timer);
		bfa_sm_set_state(dconf, bfa_dconf_sm_ready);
		break;
	case BFA_DCONF_SM_TIMEOUT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_ready);
		bfa_ioc_suspend(&dconf->bfa->ioc);
		break;
	case BFA_DCONF_SM_EXIT:
		bfa_timer_stop(&dconf->timer);
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		break;
	case BFA_DCONF_SM_IOCDISABLE:
		bfa_timer_stop(&dconf->timer);
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		break;
	default:
		bfa_sm_fault(dconf->bfa, event);
	}
}