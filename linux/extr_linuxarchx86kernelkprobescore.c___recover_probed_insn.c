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
struct kprobe {int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 int MAX_INSN_SIZE ; 
 size_t NOP_ATOMIC5 ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long ftrace_location (unsigned long) ; 
 struct kprobe* get_kprobe (void*) ; 
 int /*<<< orphan*/ * ideal_nops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ probe_kernel_read (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static unsigned long
__recover_probed_insn(kprobe_opcode_t *buf, unsigned long addr)
{
	struct kprobe *kp;
	unsigned long faddr;

	kp = get_kprobe((void *)addr);
	faddr = ftrace_location(addr);
	/*
	 * Addresses inside the ftrace location are refused by
	 * arch_check_ftrace_location(). Something went terribly wrong
	 * if such an address is checked here.
	 */
	if (WARN_ON(faddr && faddr != addr))
		return 0UL;
	/*
	 * Use the current code if it is not modified by Kprobe
	 * and it cannot be modified by ftrace.
	 */
	if (!kp && !faddr)
		return addr;

	/*
	 * Basically, kp->ainsn.insn has an original instruction.
	 * However, RIP-relative instruction can not do single-stepping
	 * at different place, __copy_instruction() tweaks the displacement of
	 * that instruction. In that case, we can't recover the instruction
	 * from the kp->ainsn.insn.
	 *
	 * On the other hand, in case on normal Kprobe, kp->opcode has a copy
	 * of the first byte of the probed instruction, which is overwritten
	 * by int3. And the instruction at kp->addr is not modified by kprobes
	 * except for the first byte, we can recover the original instruction
	 * from it and kp->opcode.
	 *
	 * In case of Kprobes using ftrace, we do not have a copy of
	 * the original instruction. In fact, the ftrace location might
	 * be modified at anytime and even could be in an inconsistent state.
	 * Fortunately, we know that the original code is the ideal 5-byte
	 * long NOP.
	 */
	if (probe_kernel_read(buf, (void *)addr,
		MAX_INSN_SIZE * sizeof(kprobe_opcode_t)))
		return 0UL;

	if (faddr)
		memcpy(buf, ideal_nops[NOP_ATOMIC5], 5);
	else
		buf[0] = kp->opcode;
	return (unsigned long)buf;
}