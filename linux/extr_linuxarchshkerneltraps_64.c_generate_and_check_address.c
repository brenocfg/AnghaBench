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
struct pt_regs {scalar_t__* regs; } ;
typedef  int insn_size_t ;
typedef  scalar_t__ __u64 ;
typedef  int __s64 ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_SW_EMULATION_FAULTS ; 
 scalar_t__ TASK_SIZE ; 
 int /*<<< orphan*/  address_is_sign_extended (scalar_t__) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  inc_unaligned_byte_access () ; 
 int /*<<< orphan*/  inc_unaligned_dword_access () ; 
 int /*<<< orphan*/  inc_unaligned_kernel_access () ; 
 int /*<<< orphan*/  inc_unaligned_multi_access () ; 
 int /*<<< orphan*/  inc_unaligned_user_access () ; 
 int /*<<< orphan*/  inc_unaligned_word_access () ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,scalar_t__) ; 
 int sign_extend64 (int,int) ; 
 int /*<<< orphan*/  unaligned_fixups_notify (int /*<<< orphan*/ ,int,struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int generate_and_check_address(struct pt_regs *regs,
				      insn_size_t opcode,
				      int displacement_not_indexed,
				      int width_shift,
				      __u64 *address)
{
	__u64 base_address, addr;
	int basereg;

	switch (1 << width_shift) {
	case 1: inc_unaligned_byte_access(); break;
	case 2: inc_unaligned_word_access(); break;
	case 4: inc_unaligned_dword_access(); break;
	case 8: inc_unaligned_multi_access(); break;
	}

	basereg = (opcode >> 20) & 0x3f;
	base_address = regs->regs[basereg];
	if (displacement_not_indexed) {
		__s64 displacement;
		displacement = (opcode >> 10) & 0x3ff;
		displacement = sign_extend64(displacement, 9);
		addr = (__u64)((__s64)base_address + (displacement << width_shift));
	} else {
		__u64 offset;
		int offsetreg;
		offsetreg = (opcode >> 10) & 0x3f;
		offset = regs->regs[offsetreg];
		addr = base_address + offset;
	}

	/* Check sign extended */
	if (!address_is_sign_extended(addr))
		return -1;

	/* Check accessible.  For misaligned access in the kernel, assume the
	   address is always accessible (and if not, just fault when the
	   load/store gets done.) */
	if (user_mode(regs)) {
		inc_unaligned_user_access();

		if (addr >= TASK_SIZE)
			return -1;
	} else
		inc_unaligned_kernel_access();

	*address = addr;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, addr);
	unaligned_fixups_notify(current, opcode, regs);

	return 0;
}