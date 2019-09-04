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
struct pt_regs {unsigned long ip; unsigned long sp; unsigned int cs; unsigned int ss; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  X86_BUG_NULL_SEG ; 
 int /*<<< orphan*/  X86_EFLAGS_IF ; 
 unsigned int __USER_DS ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  force_iret () ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  load_gs_index (unsigned int) ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_thread_common(struct pt_regs *regs, unsigned long new_ip,
		    unsigned long new_sp,
		    unsigned int _cs, unsigned int _ss, unsigned int _ds)
{
	WARN_ON_ONCE(regs != current_pt_regs());

	if (static_cpu_has(X86_BUG_NULL_SEG)) {
		/* Loading zero below won't clear the base. */
		loadsegment(fs, __USER_DS);
		load_gs_index(__USER_DS);
	}

	loadsegment(fs, 0);
	loadsegment(es, _ds);
	loadsegment(ds, _ds);
	load_gs_index(0);

	regs->ip		= new_ip;
	regs->sp		= new_sp;
	regs->cs		= _cs;
	regs->ss		= _ss;
	regs->flags		= X86_EFLAGS_IF;
	force_iret();
}