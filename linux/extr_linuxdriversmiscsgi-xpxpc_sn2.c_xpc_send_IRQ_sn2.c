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
typedef  int /*<<< orphan*/  u64 ;
struct amo {int /*<<< orphan*/  variable; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  FETCHOP_OR ; 
 int /*<<< orphan*/  FETCHOP_STORE_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GLOBAL_MMR_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NASID_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TO_AMO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sn_send_IPI_phys (int,int,int,int /*<<< orphan*/ ) ; 
 int xpPioReadError ; 
 int xpSuccess ; 
 int xp_nofault_PIOR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xp_nofault_PIOR_target ; 

__attribute__((used)) static enum xp_retval
xpc_send_IRQ_sn2(struct amo *amo, u64 flag, int nasid, int phys_cpuid,
		 int vector)
{
	int ret = 0;
	unsigned long irq_flags;

	local_irq_save(irq_flags);

	FETCHOP_STORE_OP(TO_AMO((u64)&amo->variable), FETCHOP_OR, flag);
	sn_send_IPI_phys(nasid, phys_cpuid, vector, 0);

	/*
	 * We must always use the nofault function regardless of whether we
	 * are on a Shub 1.1 system or a Shub 1.2 slice 0xc processor. If we
	 * didn't, we'd never know that the other partition is down and would
	 * keep sending IRQs and amos to it until the heartbeat times out.
	 */
	ret = xp_nofault_PIOR((u64 *)GLOBAL_MMR_ADDR(NASID_GET(&amo->variable),
						     xp_nofault_PIOR_target));

	local_irq_restore(irq_flags);

	return (ret == 0) ? xpSuccess : xpPioReadError;
}