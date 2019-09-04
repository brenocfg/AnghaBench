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
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; } ;
struct TYPE_3__ {int* bytes; } ;
struct insn {TYPE_2__ modrm; TYPE_1__ opcode; } ;

/* Variables and functions */
 int EINVAL ; 
 int UMIP_INST_SGDT ; 
 int UMIP_INST_SIDT ; 
 int UMIP_INST_SLDT ; 
 int UMIP_INST_SMSW ; 
 int UMIP_INST_STR ; 
 int X86_MODRM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insn_get_modrm (struct insn*) ; 

__attribute__((used)) static int identify_insn(struct insn *insn)
{
	/* By getting modrm we also get the opcode. */
	insn_get_modrm(insn);

	if (!insn->modrm.nbytes)
		return -EINVAL;

	/* All the instructions of interest start with 0x0f. */
	if (insn->opcode.bytes[0] != 0xf)
		return -EINVAL;

	if (insn->opcode.bytes[1] == 0x1) {
		switch (X86_MODRM_REG(insn->modrm.value)) {
		case 0:
			return UMIP_INST_SGDT;
		case 1:
			return UMIP_INST_SIDT;
		case 4:
			return UMIP_INST_SMSW;
		default:
			return -EINVAL;
		}
	} else if (insn->opcode.bytes[1] == 0x0) {
		if (X86_MODRM_REG(insn->modrm.value) == 0)
			return UMIP_INST_SLDT;
		else if (X86_MODRM_REG(insn->modrm.value) == 1)
			return UMIP_INST_STR;
		else
			return -EINVAL;
	} else {
		return -EINVAL;
	}
}