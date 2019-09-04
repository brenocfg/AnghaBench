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
struct TYPE_2__ {int simmediate; } ;
union mips_instruction {TYPE_1__ i_format; } ;
struct stackframe {scalar_t__ pc; size_t sp; int ra; } ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ get_mem (unsigned long,unsigned long*) ; 
 scalar_t__ is_end_of_function_marker (union mips_instruction*) ; 
 scalar_t__ is_ra_save_ins (union mips_instruction*) ; 
 scalar_t__ is_sp_move_ins (union mips_instruction*) ; 

__attribute__((used)) static inline int unwind_user_frame(struct stackframe *old_frame,
				    const unsigned int max_instr_check)
{
	struct stackframe new_frame = *old_frame;
	off_t ra_offset = 0;
	size_t stack_size = 0;
	unsigned long addr;

	if (old_frame->pc == 0 || old_frame->sp == 0 || old_frame->ra == 0)
		return -9;

	for (addr = new_frame.pc; (addr + max_instr_check > new_frame.pc)
		&& (!ra_offset || !stack_size); --addr) {
		union mips_instruction ip;

		if (get_mem(addr, (unsigned long *) &ip))
			return -11;

		if (is_sp_move_ins(&ip)) {
			int stack_adjustment = ip.i_format.simmediate;
			if (stack_adjustment > 0)
				/* This marks the end of the previous function,
				   which means we overran. */
				break;
			stack_size = (unsigned long) stack_adjustment;
		} else if (is_ra_save_ins(&ip)) {
			int ra_slot = ip.i_format.simmediate;
			if (ra_slot < 0)
				/* This shouldn't happen. */
				break;
			ra_offset = ra_slot;
		} else if (is_end_of_function_marker(&ip))
			break;
	}

	if (!ra_offset || !stack_size)
		goto done;

	if (ra_offset) {
		new_frame.ra = old_frame->sp + ra_offset;
		if (get_mem(new_frame.ra, &(new_frame.ra)))
			return -13;
	}

	if (stack_size) {
		new_frame.sp = old_frame->sp + stack_size;
		if (get_mem(new_frame.sp, &(new_frame.sp)))
			return -14;
	}

	if (new_frame.sp > old_frame->sp)
		return -2;

done:
	new_frame.pc = old_frame->ra;
	*old_frame = new_frame;

	return 0;
}