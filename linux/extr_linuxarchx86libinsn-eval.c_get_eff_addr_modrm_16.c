#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {int value; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; } ;
struct insn {int addr_bytes; TYPE_2__ displacement; TYPE_1__ modrm; } ;

/* Variables and functions */
 int EDOM ; 
 int EINVAL ; 
 int X86_MODRM_MOD (int /*<<< orphan*/ ) ; 
 int get_reg_offset_16 (struct insn*,struct pt_regs*,int*,int*) ; 
 int /*<<< orphan*/  insn_get_modrm (struct insn*) ; 
 int regs_get_register (struct pt_regs*,int) ; 

__attribute__((used)) static int get_eff_addr_modrm_16(struct insn *insn, struct pt_regs *regs,
				 int *regoff, short *eff_addr)
{
	int addr_offset1, addr_offset2, ret;
	short addr1 = 0, addr2 = 0, displacement;

	if (insn->addr_bytes != 2)
		return -EINVAL;

	insn_get_modrm(insn);

	if (!insn->modrm.nbytes)
		return -EINVAL;

	if (X86_MODRM_MOD(insn->modrm.value) > 2)
		return -EINVAL;

	ret = get_reg_offset_16(insn, regs, &addr_offset1, &addr_offset2);
	if (ret < 0)
		return -EINVAL;

	/*
	 * Don't fail on invalid offset values. They might be invalid because
	 * they cannot be used for this particular value of ModRM. Instead, use
	 * them in the computation only if they contain a valid value.
	 */
	if (addr_offset1 != -EDOM)
		addr1 = regs_get_register(regs, addr_offset1) & 0xffff;

	if (addr_offset2 != -EDOM)
		addr2 = regs_get_register(regs, addr_offset2) & 0xffff;

	displacement = insn->displacement.value & 0xffff;
	*eff_addr = addr1 + addr2 + displacement;

	/*
	 * The first operand register could indicate to use of either SS or DS
	 * registers to obtain the segment selector.  The second operand
	 * register can only indicate the use of DS. Thus, the first operand
	 * will be used to obtain the segment selector.
	 */
	*regoff = addr_offset1;

	return 0;
}