#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long dar; } ;
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;
struct TYPE_6__ {TYPE_1__* mm; } ;
struct TYPE_5__ {unsigned long slb_addr_limit; } ;
struct TYPE_4__ {TYPE_2__ context; } ;

/* Variables and functions */
 unsigned long H_PGTABLE_RANGE ; 
 unsigned long MAX_EA_BITS_PER_CONTEXT ; 
 scalar_t__ REGION_ID (unsigned long) ; 
 unsigned long REGION_MASK ; 
 int /*<<< orphan*/  SEGV_BNDERR ; 
 int /*<<< orphan*/  SIGSEGV ; 
 scalar_t__ USER_REGION_ID ; 
 int /*<<< orphan*/  _exception (int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bad_page_fault (struct pt_regs*,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int exception_enter () ; 
 int /*<<< orphan*/  exception_exit (int) ; 
 int get_ea_context (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  handle_multi_context_slb_miss (int,unsigned long) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void slb_miss_large_addr(struct pt_regs *regs)
{
	enum ctx_state prev_state = exception_enter();
	unsigned long ea = regs->dar;
	int context;

	if (REGION_ID(ea) != USER_REGION_ID)
		goto slb_bad_addr;

	/*
	 * Are we beyound what the page table layout supports ?
	 */
	if ((ea & ~REGION_MASK) >= H_PGTABLE_RANGE)
		goto slb_bad_addr;

	/* Lower address should have been handled by asm code */
	if (ea < (1UL << MAX_EA_BITS_PER_CONTEXT))
		goto slb_bad_addr;

	/*
	 * consider this as bad access if we take a SLB miss
	 * on an address above addr limit.
	 */
	if (ea >= current->mm->context.slb_addr_limit)
		goto slb_bad_addr;

	context = get_ea_context(&current->mm->context, ea);
	if (!context)
		goto slb_bad_addr;

	handle_multi_context_slb_miss(context, ea);
	exception_exit(prev_state);
	return;

slb_bad_addr:
	if (user_mode(regs))
		_exception(SIGSEGV, regs, SEGV_BNDERR, ea);
	else
		bad_page_fault(regs, ea, SIGSEGV);
	exception_exit(prev_state);
}