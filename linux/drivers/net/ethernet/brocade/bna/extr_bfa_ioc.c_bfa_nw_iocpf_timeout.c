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
struct TYPE_2__ {int /*<<< orphan*/  fsm; } ;
struct bfa_ioc {TYPE_1__ iocpf; } ;
typedef  enum bfa_iocpf_state { ____Placeholder_bfa_iocpf_state } bfa_iocpf_state ;

/* Variables and functions */
 int BFA_IOCPF_HWINIT ; 
 int /*<<< orphan*/  IOCPF_E_TIMEOUT ; 
 int /*<<< orphan*/  bfa_fsm_send_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_poll_fwinit (struct bfa_ioc*) ; 
 int bfa_sm_to_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iocpf_sm_table ; 

void
bfa_nw_iocpf_timeout(struct bfa_ioc *ioc)
{
	enum bfa_iocpf_state iocpf_st;

	iocpf_st = bfa_sm_to_state(iocpf_sm_table, ioc->iocpf.fsm);

	if (iocpf_st == BFA_IOCPF_HWINIT)
		bfa_ioc_poll_fwinit(ioc);
	else
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_TIMEOUT);
}