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
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_abort_decode (unsigned int) ; 
 int /*<<< orphan*/  pr_alert (char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  show_pte (unsigned long) ; 

__attribute__((used)) static void die_kernel_fault(const char *msg, unsigned long addr,
			     unsigned int esr, struct pt_regs *regs)
{
	bust_spinlocks(1);

	pr_alert("Unable to handle kernel %s at virtual address %016lx\n", msg,
		 addr);

	mem_abort_decode(esr);

	show_pte(addr);
	die("Oops", regs, esr);
	bust_spinlocks(0);
	do_exit(SIGKILL);
}