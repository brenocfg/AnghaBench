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
typedef  int u64 ;
typedef  int u32 ;
struct pt_regs {int* regs; int hi; int lo; } ;
typedef  int s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 size_t MIPSInst_RS (int) ; 
 size_t MIPSInst_RT (int) ; 
 int /*<<< orphan*/  MIPS_R2_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsps ; 

__attribute__((used)) static int msubu_func(struct pt_regs *regs, u32 ir)
{
	u64 res;
	u32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (u64)rt * (u64)rs;
	rt = regs->hi;
	rs = regs->lo;
	res = ((((s64)rt) << 32) | (u32)rs) - res;

	rt = res;
	regs->lo = (s64)(s32)rt;
	rs = res >> 32;
	regs->hi = (s64)(s32)rs;

	MIPS_R2_STATS(dsps);

	return 0;
}