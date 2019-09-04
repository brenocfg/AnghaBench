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
union mips_instruction {int* halfword; int word; } ;
typedef  int /*<<< orphan*/  ulong ;
struct mips_frame_info {int pc_offset; int /*<<< orphan*/  frame_size; scalar_t__ func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_MICROMIPS ; 
 int IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ is_jump_ins (union mips_instruction*) ; 
 scalar_t__ is_ra_save_ins (union mips_instruction*,int*) ; 
 int /*<<< orphan*/  is_sp_move_ins (union mips_instruction*,int /*<<< orphan*/ *) ; 
 scalar_t__ mm_insn_16bit (int) ; 
 scalar_t__ msk_isa16_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_frame_info(struct mips_frame_info *info)
{
	bool is_mmips = IS_ENABLED(CONFIG_CPU_MICROMIPS);
	union mips_instruction insn, *ip;
	const unsigned int max_insns = 128;
	unsigned int last_insn_size = 0;
	unsigned int i;
	bool saw_jump = false;

	info->pc_offset = -1;
	info->frame_size = 0;

	ip = (void *)msk_isa16_mode((ulong)info->func);
	if (!ip)
		goto err;

	for (i = 0; i < max_insns; i++) {
		ip = (void *)ip + last_insn_size;

		if (is_mmips && mm_insn_16bit(ip->halfword[0])) {
			insn.word = ip->halfword[0] << 16;
			last_insn_size = 2;
		} else if (is_mmips) {
			insn.word = ip->halfword[0] << 16 | ip->halfword[1];
			last_insn_size = 4;
		} else {
			insn.word = ip->word;
			last_insn_size = 4;
		}

		if (!info->frame_size) {
			is_sp_move_ins(&insn, &info->frame_size);
			continue;
		} else if (!saw_jump && is_jump_ins(ip)) {
			/*
			 * If we see a jump instruction, we are finished
			 * with the frame save.
			 *
			 * Some functions can have a shortcut return at
			 * the beginning of the function, so don't start
			 * looking for jump instruction until we see the
			 * frame setup.
			 *
			 * The RA save instruction can get put into the
			 * delay slot of the jump instruction, so look
			 * at the next instruction, too.
			 */
			saw_jump = true;
			continue;
		}
		if (info->pc_offset == -1 &&
		    is_ra_save_ins(&insn, &info->pc_offset))
			break;
		if (saw_jump)
			break;
	}
	if (info->frame_size && info->pc_offset >= 0) /* nested */
		return 0;
	if (info->pc_offset < 0) /* leaf */
		return 1;
	/* prologue seems bogus... */
err:
	return -1;
}