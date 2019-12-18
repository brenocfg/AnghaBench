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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_sem_reg; } ;
struct bfa_ioc_s {int /*<<< orphan*/  iocpf; TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCPF_E_SEMLOCKED ; 
 int /*<<< orphan*/  IOCPF_E_SEM_ERROR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sem_timer_start (struct bfa_ioc_s*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_hw_sem_get(struct bfa_ioc_s *ioc)
{
	u32	r32;

	/*
	 * First read to the semaphore register will return 0, subsequent reads
	 * will return 1. Semaphore is released by writing 1 to the register
	 */
	r32 = readl(ioc->ioc_regs.ioc_sem_reg);
	if (r32 == ~0) {
		WARN_ON(r32 == ~0);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEM_ERROR);
		return;
	}
	if (!(r32 & 1)) {
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEMLOCKED);
		return;
	}

	bfa_sem_timer_start(ioc);
}