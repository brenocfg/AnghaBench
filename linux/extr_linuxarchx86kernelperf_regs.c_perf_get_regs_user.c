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
struct pt_regs {unsigned long sp; int bx; int r12; int r13; int r14; int r15; int /*<<< orphan*/  bp; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  flags; int /*<<< orphan*/  orig_ax; scalar_t__ r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  ax; int /*<<< orphan*/  ip; } ;
struct perf_regs {struct pt_regs* regs; int /*<<< orphan*/  abi; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI_32 ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI_64 ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI_NONE ; 
 int /*<<< orphan*/  current ; 
 struct pt_regs* task_pt_regs (int /*<<< orphan*/ ) ; 
 scalar_t__ user_64bit_mode (struct pt_regs*) ; 

void perf_get_regs_user(struct perf_regs *regs_user,
			struct pt_regs *regs,
			struct pt_regs *regs_user_copy)
{
	struct pt_regs *user_regs = task_pt_regs(current);

	/*
	 * If we're in an NMI that interrupted task_pt_regs setup, then
	 * we can't sample user regs at all.  This check isn't really
	 * sufficient, though, as we could be in an NMI inside an interrupt
	 * that happened during task_pt_regs setup.
	 */
	if (regs->sp > (unsigned long)&user_regs->r11 &&
	    regs->sp <= (unsigned long)(user_regs + 1)) {
		regs_user->abi = PERF_SAMPLE_REGS_ABI_NONE;
		regs_user->regs = NULL;
		return;
	}

	/*
	 * These registers are always saved on 64-bit syscall entry.
	 * On 32-bit entry points, they are saved too except r8..r11.
	 */
	regs_user_copy->ip = user_regs->ip;
	regs_user_copy->ax = user_regs->ax;
	regs_user_copy->cx = user_regs->cx;
	regs_user_copy->dx = user_regs->dx;
	regs_user_copy->si = user_regs->si;
	regs_user_copy->di = user_regs->di;
	regs_user_copy->r8 = user_regs->r8;
	regs_user_copy->r9 = user_regs->r9;
	regs_user_copy->r10 = user_regs->r10;
	regs_user_copy->r11 = user_regs->r11;
	regs_user_copy->orig_ax = user_regs->orig_ax;
	regs_user_copy->flags = user_regs->flags;
	regs_user_copy->sp = user_regs->sp;
	regs_user_copy->cs = user_regs->cs;
	regs_user_copy->ss = user_regs->ss;
	/*
	 * Store user space frame-pointer value on sample
	 * to facilitate stack unwinding for cases when
	 * user space executable code has such support
	 * enabled at compile time:
	 */
	regs_user_copy->bp = user_regs->bp;

	regs_user_copy->bx = -1;
	regs_user_copy->r12 = -1;
	regs_user_copy->r13 = -1;
	regs_user_copy->r14 = -1;
	regs_user_copy->r15 = -1;
	/*
	 * For this to be at all useful, we need a reasonable guess for
	 * the ABI.  Be careful: we're in NMI context, and we're
	 * considering current to be the current task, so we should
	 * be careful not to look at any other percpu variables that might
	 * change during context switches.
	 */
	regs_user->abi = user_64bit_mode(user_regs) ?
		PERF_SAMPLE_REGS_ABI_64 : PERF_SAMPLE_REGS_ABI_32;

	regs_user->regs = regs_user_copy;
}