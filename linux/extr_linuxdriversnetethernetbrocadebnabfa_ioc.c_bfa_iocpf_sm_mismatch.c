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
struct bfa_iocpf {struct bfa_ioc* ioc; } ;
struct bfa_ioc {int /*<<< orphan*/  iocpf_timer; } ;
typedef  enum iocpf_event { ____Placeholder_iocpf_event } iocpf_event ;

/* Variables and functions */
#define  IOCPF_E_DISABLE 130 
#define  IOCPF_E_STOP 129 
#define  IOCPF_E_TIMEOUT 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_pf_disabled (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_iocpf_sm_fwcheck ; 
 int /*<<< orphan*/  bfa_iocpf_sm_reset ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_iocpf_sm_mismatch(struct bfa_iocpf *iocpf, enum iocpf_event event)
{
	struct bfa_ioc *ioc = iocpf->ioc;

	switch (event) {
	case IOCPF_E_TIMEOUT:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fwcheck);
		break;

	case IOCPF_E_DISABLE:
		del_timer(&ioc->iocpf_timer);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		bfa_ioc_pf_disabled(ioc);
		break;

	case IOCPF_E_STOP:
		del_timer(&ioc->iocpf_timer);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		break;

	default:
		bfa_sm_fault(event);
	}
}