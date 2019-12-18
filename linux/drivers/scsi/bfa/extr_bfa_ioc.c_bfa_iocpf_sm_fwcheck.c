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
struct bfa_iocpf_s {struct bfa_ioc_s* ioc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_sem_reg; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;
typedef  enum iocpf_event { ____Placeholder_iocpf_event } iocpf_event ;

/* Variables and functions */
#define  IOCPF_E_DISABLE 131 
#define  IOCPF_E_SEMLOCKED 130 
#define  IOCPF_E_SEM_ERROR 129 
#define  IOCPF_E_STOP 128 
 int /*<<< orphan*/  IOC_E_DISABLED ; 
 int /*<<< orphan*/  IOC_E_HWFAILED ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_firmware_lock (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_firmware_unlock (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_sync_join (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_sync_start (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_iocpf_sm_fail ; 
 int /*<<< orphan*/  bfa_iocpf_sm_hwinit ; 
 int /*<<< orphan*/  bfa_iocpf_sm_mismatch ; 
 int /*<<< orphan*/  bfa_iocpf_sm_reset ; 
 int /*<<< orphan*/  bfa_sem_timer_start (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_sem_timer_stop (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_sm_fault (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_fwcheck(struct bfa_iocpf_s *iocpf, enum iocpf_event event)
{
	struct bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	switch (event) {
	case IOCPF_E_SEMLOCKED:
		if (bfa_ioc_firmware_lock(ioc)) {
			if (bfa_ioc_sync_start(ioc)) {
				bfa_ioc_sync_join(ioc);
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
			} else {
				bfa_ioc_firmware_unlock(ioc);
				writel(1, ioc->ioc_regs.ioc_sem_reg);
				bfa_sem_timer_start(ioc);
			}
		} else {
			writel(1, ioc->ioc_regs.ioc_sem_reg);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_mismatch);
		}
		break;

	case IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
		break;

	case IOCPF_E_DISABLE:
		bfa_sem_timer_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		bfa_fsm_send_event(ioc, IOC_E_DISABLED);
		break;

	case IOCPF_E_STOP:
		bfa_sem_timer_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		break;

	default:
		bfa_sm_fault(ioc, event);
	}
}