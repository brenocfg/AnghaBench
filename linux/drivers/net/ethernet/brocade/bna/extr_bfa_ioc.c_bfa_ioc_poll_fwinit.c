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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ poll_time; } ;
struct bfa_ioc {int /*<<< orphan*/  iocpf_timer; TYPE_1__ iocpf; } ;

/* Variables and functions */
 scalar_t__ BFA_IOC_POLL_TOV ; 
 scalar_t__ BFA_IOC_TOV ; 
 scalar_t__ BFI_IOC_DISABLED ; 
 int /*<<< orphan*/  IOCPF_E_FWREADY ; 
 int /*<<< orphan*/  IOCPF_E_TIMEOUT ; 
 int /*<<< orphan*/  bfa_fsm_send_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_ioc_get_cur_ioc_fwstate (struct bfa_ioc*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void
bfa_ioc_poll_fwinit(struct bfa_ioc *ioc)
{
	u32 fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);

	if (fwstate == BFI_IOC_DISABLED) {
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		return;
	}

	if (ioc->iocpf.poll_time >= BFA_IOC_TOV) {
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_TIMEOUT);
	} else {
		ioc->iocpf.poll_time += BFA_IOC_POLL_TOV;
		mod_timer(&ioc->iocpf_timer, jiffies +
			msecs_to_jiffies(BFA_IOC_POLL_TOV));
	}
}