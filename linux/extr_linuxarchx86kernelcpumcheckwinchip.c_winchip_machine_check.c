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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  TAINT_MACHINE_CHECK ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ist_enter (struct pt_regs*) ; 
 int /*<<< orphan*/  ist_exit (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

__attribute__((used)) static void winchip_machine_check(struct pt_regs *regs, long error_code)
{
	ist_enter(regs);

	pr_emerg("CPU0: Machine Check Exception.\n");
	add_taint(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

	ist_exit(regs);
}