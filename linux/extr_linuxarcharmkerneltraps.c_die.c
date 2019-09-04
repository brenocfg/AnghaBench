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
struct pt_regs {int /*<<< orphan*/  ARM_pc; } ;
typedef  enum bug_trap_type { ____Placeholder_bug_trap_type } bug_trap_type ;

/* Variables and functions */
 int BUG_TRAP_TYPE_NONE ; 
 int SIGSEGV ; 
 scalar_t__ __die (char const*,int,struct pt_regs*) ; 
 unsigned long oops_begin () ; 
 int /*<<< orphan*/  oops_end (unsigned long,struct pt_regs*,int) ; 
 int report_bug (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void die(const char *str, struct pt_regs *regs, int err)
{
	enum bug_trap_type bug_type = BUG_TRAP_TYPE_NONE;
	unsigned long flags = oops_begin();
	int sig = SIGSEGV;

	if (!user_mode(regs))
		bug_type = report_bug(regs->ARM_pc, regs);
	if (bug_type != BUG_TRAP_TYPE_NONE)
		str = "Oops - BUG";

	if (__die(str, err, regs))
		sig = 0;

	oops_end(flags, regs, sig);
}