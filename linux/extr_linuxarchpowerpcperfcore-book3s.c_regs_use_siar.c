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
struct pt_regs {scalar_t__ result; } ;

/* Variables and functions */
 int TRAP (struct pt_regs*) ; 

__attribute__((used)) static bool regs_use_siar(struct pt_regs *regs)
{
	/*
	 * When we take a performance monitor exception the regs are setup
	 * using perf_read_regs() which overloads some fields, in particular
	 * regs->result to tell us whether to use SIAR.
	 *
	 * However if the regs are from another exception, eg. a syscall, then
	 * they have not been setup using perf_read_regs() and so regs->result
	 * is something random.
	 */
	return ((TRAP(regs) == 0xf00) && regs->result);
}