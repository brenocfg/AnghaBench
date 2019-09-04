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
struct TYPE_2__ {scalar_t__* bytes; } ;
struct insn {scalar_t__ length; TYPE_1__ opcode; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 scalar_t__ BREAKPOINT_INSTRUCTION ; 
 int MAX_INSN_SIZE ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 int /*<<< orphan*/  kallsyms_lookup_size_offset (unsigned long,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  kernel_insn_init (struct insn*,void*,int) ; 
 unsigned long recover_probed_instruction (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int can_probe(unsigned long paddr)
{
	unsigned long addr, __addr, offset = 0;
	struct insn insn;
	kprobe_opcode_t buf[MAX_INSN_SIZE];

	if (!kallsyms_lookup_size_offset(paddr, NULL, &offset))
		return 0;

	/* Decode instructions */
	addr = paddr - offset;
	while (addr < paddr) {
		/*
		 * Check if the instruction has been modified by another
		 * kprobe, in which case we replace the breakpoint by the
		 * original instruction in our buffer.
		 * Also, jump optimization will change the breakpoint to
		 * relative-jump. Since the relative-jump itself is
		 * normally used, we just go through if there is no kprobe.
		 */
		__addr = recover_probed_instruction(buf, addr);
		if (!__addr)
			return 0;
		kernel_insn_init(&insn, (void *)__addr, MAX_INSN_SIZE);
		insn_get_length(&insn);

		/*
		 * Another debugging subsystem might insert this breakpoint.
		 * In that case, we can't recover it.
		 */
		if (insn.opcode.bytes[0] == BREAKPOINT_INSTRUCTION)
			return 0;
		addr += insn.length;
	}

	return (addr == paddr);
}