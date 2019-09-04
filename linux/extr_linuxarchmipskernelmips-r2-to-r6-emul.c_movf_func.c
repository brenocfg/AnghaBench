#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pt_regs {int /*<<< orphan*/ * regs; } ;
struct TYPE_4__ {int fcr31; } ;
struct TYPE_5__ {TYPE_1__ fpu; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 size_t MIPSInst_RD (int) ; 
 size_t MIPSInst_RS (int) ; 
 int MIPSInst_RT (int) ; 
 int /*<<< orphan*/  MIPS_R2_STATS (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int* fpucondbit ; 
 int /*<<< orphan*/  movs ; 

__attribute__((used)) static int movf_func(struct pt_regs *regs, u32 ir)
{
	u32 csr;
	u32 cond;

	csr = current->thread.fpu.fcr31;
	cond = fpucondbit[MIPSInst_RT(ir) >> 2];

	if (((csr & cond) == 0) && MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->regs[MIPSInst_RS(ir)];

	MIPS_R2_STATS(movs);

	return 0;
}