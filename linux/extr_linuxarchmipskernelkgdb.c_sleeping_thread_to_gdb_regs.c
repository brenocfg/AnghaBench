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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  reg31; int /*<<< orphan*/  cp0_status; int /*<<< orphan*/  reg30; int /*<<< orphan*/  reg29; int /*<<< orphan*/  reg23; int /*<<< orphan*/  reg22; int /*<<< orphan*/  reg21; int /*<<< orphan*/  reg20; int /*<<< orphan*/  reg19; int /*<<< orphan*/  reg18; int /*<<< orphan*/  reg17; int /*<<< orphan*/  reg16; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	int reg;
#if (KGDB_GDB_REG_SIZE == 32)
	u32 *ptr = (u32 *)gdb_regs;
#else
	u64 *ptr = (u64 *)gdb_regs;
#endif

	for (reg = 0; reg < 16; reg++)
		*(ptr++) = 0;

	/* S0 - S7 */
	*(ptr++) = p->thread.reg16;
	*(ptr++) = p->thread.reg17;
	*(ptr++) = p->thread.reg18;
	*(ptr++) = p->thread.reg19;
	*(ptr++) = p->thread.reg20;
	*(ptr++) = p->thread.reg21;
	*(ptr++) = p->thread.reg22;
	*(ptr++) = p->thread.reg23;

	for (reg = 24; reg < 28; reg++)
		*(ptr++) = 0;

	/* GP, SP, FP, RA */
	*(ptr++) = (long)p;
	*(ptr++) = p->thread.reg29;
	*(ptr++) = p->thread.reg30;
	*(ptr++) = p->thread.reg31;

	*(ptr++) = p->thread.cp0_status;

	/* lo, hi */
	*(ptr++) = 0;
	*(ptr++) = 0;

	/*
	 * BadVAddr, Cause
	 * Ideally these would come from the last exception frame up the stack
	 * but that requires unwinding, otherwise we can't know much for sure.
	 */
	*(ptr++) = 0;
	*(ptr++) = 0;

	/*
	 * PC
	 * use return address (RA), i.e. the moment after return from resume()
	 */
	*(ptr++) = p->thread.reg31;
}