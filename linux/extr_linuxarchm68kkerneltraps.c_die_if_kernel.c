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
struct pt_regs {int sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int PS_S ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*,char*,int) ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 

void die_if_kernel (char *str, struct pt_regs *fp, int nr)
{
	if (!(fp->sr & PS_S))
		return;

	console_verbose();
	pr_crit("%s: %08x\n", str, nr);
	show_registers(fp);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	do_exit(SIGSEGV);
}