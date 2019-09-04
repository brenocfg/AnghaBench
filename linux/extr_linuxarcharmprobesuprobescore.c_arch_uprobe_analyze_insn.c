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
struct mm_struct {int dummy; } ;
struct arch_uprobe {int simulate; unsigned int bpinsn; int /*<<< orphan*/  asi; void** ixol; scalar_t__ insn; } ;
typedef  enum probes_insn { ____Placeholder_probes_insn } probes_insn ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_GOOD 130 
#define  INSN_GOOD_NO_SLOT 129 
#define  INSN_REJECTED 128 
 unsigned int UPROBE_SS_ARM_INSN ; 
 int UPROBE_SWBP_ARM_INSN ; 
 unsigned int __mem_to_opcode_arm (unsigned int) ; 
 void* __opcode_to_mem_arm (unsigned int) ; 
 int arm_probes_decode_insn (unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprobes_probes_actions ; 

int arch_uprobe_analyze_insn(struct arch_uprobe *auprobe, struct mm_struct *mm,
			     unsigned long addr)
{
	unsigned int insn;
	unsigned int bpinsn;
	enum probes_insn ret;

	/* Thumb not yet support */
	if (addr & 0x3)
		return -EINVAL;

	insn = __mem_to_opcode_arm(*(unsigned int *)auprobe->insn);
	auprobe->ixol[0] = __opcode_to_mem_arm(insn);
	auprobe->ixol[1] = __opcode_to_mem_arm(UPROBE_SS_ARM_INSN);

	ret = arm_probes_decode_insn(insn, &auprobe->asi, false,
				     uprobes_probes_actions, NULL);
	switch (ret) {
	case INSN_REJECTED:
		return -EINVAL;

	case INSN_GOOD_NO_SLOT:
		auprobe->simulate = true;
		break;

	case INSN_GOOD:
	default:
		break;
	}

	bpinsn = UPROBE_SWBP_ARM_INSN & 0x0fffffff;
	if (insn >= 0xe0000000)
		bpinsn |= 0xe0000000;  /* Unconditional instruction */
	else
		bpinsn |= insn & 0xf0000000;  /* Copy condition from insn */

	auprobe->bpinsn = bpinsn;

	return 0;
}