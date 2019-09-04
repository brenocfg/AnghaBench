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
struct tl1_traplog {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_TRAP_TL1 ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  dump_tl1_traplog (struct tl1_traplog*) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char*,struct pt_regs*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spitfire_data_access_exception (struct pt_regs*,unsigned long,unsigned long) ; 

void spitfire_data_access_exception_tl1(struct pt_regs *regs, unsigned long sfsr, unsigned long sfar)
{
	if (notify_die(DIE_TRAP_TL1, "data access exception tl1", regs,
		       0, 0x30, SIGTRAP) == NOTIFY_STOP)
		return;

	dump_tl1_traplog((struct tl1_traplog *)(regs + 1));
	spitfire_data_access_exception(regs, sfsr, sfar);
}