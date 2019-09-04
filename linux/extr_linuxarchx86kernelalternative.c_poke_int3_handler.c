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
struct pt_regs {unsigned long ip; } ;

/* Variables and functions */
 scalar_t__ bp_int3_addr ; 
 scalar_t__ bp_int3_handler ; 
 int /*<<< orphan*/  bp_patching_in_progress ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int poke_int3_handler(struct pt_regs *regs)
{
	/*
	 * Having observed our INT3 instruction, we now must observe
	 * bp_patching_in_progress.
	 *
	 * 	in_progress = TRUE		INT3
	 * 	WMB				RMB
	 * 	write INT3			if (in_progress)
	 *
	 * Idem for bp_int3_handler.
	 */
	smp_rmb();

	if (likely(!bp_patching_in_progress))
		return 0;

	if (user_mode(regs) || regs->ip != (unsigned long)bp_int3_addr)
		return 0;

	/* set up the specified breakpoint handler */
	regs->ip = (unsigned long) bp_int3_handler;

	return 1;

}