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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; } ;
struct insn {int addr_bytes; TYPE_1__ modrm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_TYPE_RM ; 
 int X86_MODRM_MOD (int /*<<< orphan*/ ) ; 
 int get_reg_offset (struct insn*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insn_get_modrm (struct insn*) ; 
 int regs_get_register (struct pt_regs*,int) ; 

__attribute__((used)) static int get_eff_addr_reg(struct insn *insn, struct pt_regs *regs,
			    int *regoff, long *eff_addr)
{
	insn_get_modrm(insn);

	if (!insn->modrm.nbytes)
		return -EINVAL;

	if (X86_MODRM_MOD(insn->modrm.value) != 3)
		return -EINVAL;

	*regoff = get_reg_offset(insn, regs, REG_TYPE_RM);
	if (*regoff < 0)
		return -EINVAL;

	/* Ignore bytes that are outside the address size. */
	if (insn->addr_bytes == 2)
		*eff_addr = regs_get_register(regs, *regoff) & 0xffff;
	else if (insn->addr_bytes == 4)
		*eff_addr = regs_get_register(regs, *regoff) & 0xffffffff;
	else /* 64-bit address */
		*eff_addr = regs_get_register(regs, *regoff);

	return 0;
}