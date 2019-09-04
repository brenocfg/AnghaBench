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
struct pt_regs {unsigned long pc; int ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrusp (unsigned long) ; 

void
start_thread(struct pt_regs * regs, unsigned long pc, unsigned long sp)
{
	regs->pc = pc;
	regs->ps = 8;
	wrusp(sp);
}