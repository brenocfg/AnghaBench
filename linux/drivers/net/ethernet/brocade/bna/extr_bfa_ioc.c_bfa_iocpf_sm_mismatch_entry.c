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
struct bfa_iocpf {int fw_mismatch_notified; TYPE_1__* ioc; } ;
struct TYPE_2__ {int /*<<< orphan*/  iocpf_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_TOV ; 
 int /*<<< orphan*/  bfa_ioc_pf_fwmismatch (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_mismatch_entry(struct bfa_iocpf *iocpf)
{
	/* Call only the first time sm enters fwmismatch state. */
	if (!iocpf->fw_mismatch_notified)
		bfa_ioc_pf_fwmismatch(iocpf->ioc);

	iocpf->fw_mismatch_notified = true;
	mod_timer(&(iocpf->ioc)->iocpf_timer, jiffies +
		msecs_to_jiffies(BFA_IOC_TOV));
}