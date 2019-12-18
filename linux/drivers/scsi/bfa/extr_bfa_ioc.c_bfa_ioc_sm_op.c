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
struct TYPE_2__ {int /*<<< orphan*/  auto_recover; } ;
struct bfa_ioc_s {TYPE_1__ iocpf; } ;
typedef  enum ioc_event { ____Placeholder_ioc_event } ioc_event ;

/* Variables and functions */
 int /*<<< orphan*/  IOCPF_E_FAIL ; 
#define  IOC_E_DISABLE 132 
#define  IOC_E_ENABLE 131 
#define  IOC_E_HBFAIL 130 
#define  IOC_E_HWERROR 129 
#define  IOC_E_PFFAILED 128 
 int /*<<< orphan*/  bfa_fsm_send_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_hb_timer_stop (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_fail_notify (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_sm_disabling ; 
 int /*<<< orphan*/  bfa_ioc_sm_fail ; 
 int /*<<< orphan*/  bfa_ioc_sm_fail_retry ; 
 int /*<<< orphan*/  bfa_sm_fault (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 

__attribute__((used)) static void
bfa_ioc_sm_op(struct bfa_ioc_s *ioc, enum ioc_event event)
{
	bfa_trc(ioc, event);

	switch (event) {
	case IOC_E_ENABLE:
		break;

	case IOC_E_DISABLE:
		bfa_hb_timer_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		break;

	case IOC_E_PFFAILED:
	case IOC_E_HWERROR:
		bfa_hb_timer_stop(ioc);
		/* !!! fall through !!! */
	case IOC_E_HBFAIL:
		if (ioc->iocpf.auto_recover)
			bfa_fsm_set_state(ioc, bfa_ioc_sm_fail_retry);
		else
			bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);

		bfa_ioc_fail_notify(ioc);

		if (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FAIL);
		break;

	default:
		bfa_sm_fault(ioc, event);
	}
}