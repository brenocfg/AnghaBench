#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct bfa_dconf_s {int dummy; } ;
struct bfa_dconf_mod_s {int min_cfg; TYPE_1__* bfa; int /*<<< orphan*/  timer; int /*<<< orphan*/  dconf; int /*<<< orphan*/  instance; } ;
typedef  enum bfa_dconf_event { ____Placeholder_bfa_dconf_event } bfa_dconf_event ;
typedef  int /*<<< orphan*/  bfa_status_t ;
struct TYPE_8__ {int /*<<< orphan*/  iocfc; } ;

/* Variables and functions */
#define  BFA_DCONF_SM_EXIT 132 
#define  BFA_DCONF_SM_FLASH_COMP 131 
#define  BFA_DCONF_SM_INIT 130 
#define  BFA_DCONF_SM_IOCDISABLE 129 
#define  BFA_DCONF_SM_WR 128 
 int BFA_DCONF_UPDATE_TOV ; 
 int /*<<< orphan*/  BFA_FLASH (TYPE_1__*) ; 
 int /*<<< orphan*/  BFA_FLASH_PART_DRV ; 
 int /*<<< orphan*/  BFA_STATUS_FAILED ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  IOCFC_E_DCONF_DONE ; 
 int /*<<< orphan*/  bfa_dconf_init_cb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void bfa_dconf_sm_flash_read (struct bfa_dconf_mod_s*,int) ; 
 int /*<<< orphan*/  bfa_dconf_timer ; 
 int /*<<< orphan*/  bfa_flash_read_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ ),TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dconf_mod_s*,void (*) (struct bfa_dconf_mod_s*,int)) ; 
 int /*<<< orphan*/  bfa_timer_start (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_dconf_mod_s*,int) ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_dconf_sm_uninit(struct bfa_dconf_mod_s *dconf, enum bfa_dconf_event event)
{
	bfa_status_t bfa_status;
	bfa_trc(dconf->bfa, event);

	switch (event) {
	case BFA_DCONF_SM_INIT:
		if (dconf->min_cfg) {
			bfa_trc(dconf->bfa, dconf->min_cfg);
			bfa_fsm_send_event(&dconf->bfa->iocfc,
					IOCFC_E_DCONF_DONE);
			return;
		}
		bfa_sm_set_state(dconf, bfa_dconf_sm_flash_read);
		bfa_timer_start(dconf->bfa, &dconf->timer,
			bfa_dconf_timer, dconf, 2 * BFA_DCONF_UPDATE_TOV);
		bfa_status = bfa_flash_read_part(BFA_FLASH(dconf->bfa),
					BFA_FLASH_PART_DRV, dconf->instance,
					dconf->dconf,
					sizeof(struct bfa_dconf_s), 0,
					bfa_dconf_init_cb, dconf->bfa);
		if (bfa_status != BFA_STATUS_OK) {
			bfa_timer_stop(&dconf->timer);
			bfa_dconf_init_cb(dconf->bfa, BFA_STATUS_FAILED);
			bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
			return;
		}
		break;
	case BFA_DCONF_SM_EXIT:
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
	case BFA_DCONF_SM_IOCDISABLE:
	case BFA_DCONF_SM_WR:
	case BFA_DCONF_SM_FLASH_COMP:
		break;
	default:
		bfa_sm_fault(dconf->bfa, event);
	}
}