#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;
struct pt_regs {TYPE_1__ psw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILL_PRVOPC ; 
 int /*<<< orphan*/  PSW_ASC_HOME ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  do_trap (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void space_switch_exception(struct pt_regs *regs)
{
	/* Set user psw back to home space mode. */
	if (user_mode(regs))
		regs->psw.mask |= PSW_ASC_HOME;
	/* Send SIGILL. */
	do_trap(regs, SIGILL, ILL_PRVOPC, "space switch event");
}