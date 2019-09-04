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
struct pt_regs {int dummy; } ;
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; } ;
struct insn {int addr_bytes; TYPE_3__ displacement; TYPE_2__ sib; TYPE_1__ modrm; } ;

/* Variables and functions */
 int EDOM ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_TYPE_BASE ; 
 int /*<<< orphan*/  REG_TYPE_INDEX ; 
 int X86_MODRM_MOD (int /*<<< orphan*/ ) ; 
 int X86_SIB_SCALE (int /*<<< orphan*/ ) ; 
 int get_reg_offset (struct insn*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insn_get_modrm (struct insn*) ; 
 int /*<<< orphan*/  insn_get_sib (struct insn*) ; 
 long regs_get_register (struct pt_regs*,int) ; 

__attribute__((used)) static int get_eff_addr_sib(struct insn *insn, struct pt_regs *regs,
			    int *base_offset, long *eff_addr)
{
	long base, indx;
	int indx_offset;

	if (insn->addr_bytes != 8 && insn->addr_bytes != 4)
		return -EINVAL;

	insn_get_modrm(insn);

	if (!insn->modrm.nbytes)
		return -EINVAL;

	if (X86_MODRM_MOD(insn->modrm.value) > 2)
		return -EINVAL;

	insn_get_sib(insn);

	if (!insn->sib.nbytes)
		return -EINVAL;

	*base_offset = get_reg_offset(insn, regs, REG_TYPE_BASE);
	indx_offset = get_reg_offset(insn, regs, REG_TYPE_INDEX);

	/*
	 * Negative values in the base and index offset means an error when
	 * decoding the SIB byte. Except -EDOM, which means that the registers
	 * should not be used in the address computation.
	 */
	if (*base_offset == -EDOM)
		base = 0;
	else if (*base_offset < 0)
		return -EINVAL;
	else
		base = regs_get_register(regs, *base_offset);

	if (indx_offset == -EDOM)
		indx = 0;
	else if (indx_offset < 0)
		return -EINVAL;
	else
		indx = regs_get_register(regs, indx_offset);

	if (insn->addr_bytes == 4) {
		int addr32, base32, idx32;

		base32 = base & 0xffffffff;
		idx32 = indx & 0xffffffff;

		addr32 = base32 + idx32 * (1 << X86_SIB_SCALE(insn->sib.value));
		addr32 += insn->displacement.value;

		*eff_addr = addr32 & 0xffffffff;
	} else {
		*eff_addr = base + indx * (1 << X86_SIB_SCALE(insn->sib.value));
		*eff_addr += insn->displacement.value;
	}

	return 0;
}