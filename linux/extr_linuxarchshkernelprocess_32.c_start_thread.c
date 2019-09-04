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
struct pt_regs {unsigned long pc; unsigned long* regs; int /*<<< orphan*/  sr; scalar_t__ pr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_FD ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  free_thread_xstate (int /*<<< orphan*/ ) ; 

void start_thread(struct pt_regs *regs, unsigned long new_pc,
		  unsigned long new_sp)
{
	regs->pr = 0;
	regs->sr = SR_FD;
	regs->pc = new_pc;
	regs->regs[15] = new_sp;

	free_thread_xstate(current);
}