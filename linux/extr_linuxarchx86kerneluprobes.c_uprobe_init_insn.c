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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int nbytes; } ;
struct insn {TYPE_1__ opcode; } ;
struct arch_uprobe {int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 int ENOEXEC ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  OPCODE1 (struct insn*) ; 
 int /*<<< orphan*/  OPCODE2 (struct insn*) ; 
 scalar_t__ good_2byte_insns ; 
 int* good_insns_32 ; 
 int* good_insns_64 ; 
 int /*<<< orphan*/  insn_complete (struct insn*) ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 int /*<<< orphan*/  insn_init (struct insn*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ insn_masking_exception (struct insn*) ; 
 scalar_t__ is_prefix_bad (struct insn*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int uprobe_init_insn(struct arch_uprobe *auprobe, struct insn *insn, bool x86_64)
{
	u32 volatile *good_insns;

	insn_init(insn, auprobe->insn, sizeof(auprobe->insn), x86_64);
	/* has the side-effect of processing the entire instruction */
	insn_get_length(insn);
	if (!insn_complete(insn))
		return -ENOEXEC;

	if (is_prefix_bad(insn))
		return -ENOTSUPP;

	/* We should not singlestep on the exception masking instructions */
	if (insn_masking_exception(insn))
		return -ENOTSUPP;

	if (x86_64)
		good_insns = good_insns_64;
	else
		good_insns = good_insns_32;

	if (test_bit(OPCODE1(insn), (unsigned long *)good_insns))
		return 0;

	if (insn->opcode.nbytes == 2) {
		if (test_bit(OPCODE2(insn), (unsigned long *)good_2byte_insns))
			return 0;
	}

	return -ENOTSUPP;
}