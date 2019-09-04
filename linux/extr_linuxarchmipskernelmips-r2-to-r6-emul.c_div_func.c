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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int* regs; void* hi; void* lo; } ;
typedef  void* s64 ;
typedef  int s32 ;

/* Variables and functions */
 size_t MIPSInst_RS (int /*<<< orphan*/ ) ; 
 size_t MIPSInst_RT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPS_R2_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  divs ; 

__attribute__((used)) static int div_func(struct pt_regs *regs, u32 ir)
{
	s32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];

	regs->lo = (s64)(rs / rt);
	regs->hi = (s64)(rs % rt);

	MIPS_R2_STATS(divs);

	return 0;
}