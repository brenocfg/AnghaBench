#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ opcode; int rs; int simmediate; } ;
union mips_instruction {int word; int /*<<< orphan*/  halfword; TYPE_1__ mm_a_format; } ;
struct pt_regs {int cp0_epc; long* regs; } ;
struct emuframe {int emul; int badinst; } ;
typedef  int s32 ;
typedef  int mips_instruction ;
typedef  int /*<<< orphan*/  fr ;
struct TYPE_6__ {unsigned long bd_emu_branch_pc; unsigned long bd_emu_cont_pc; int /*<<< orphan*/  bd_emu_frame; } ;
struct TYPE_7__ {TYPE_2__ thread; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int BD_EMUFRAME_NONE ; 
 int BREAK_MATH (int) ; 
 int FOLL_FORCE ; 
 int FOLL_WRITE ; 
 int /*<<< orphan*/  MIPS_FPU_EMU_INC_STATS (int /*<<< orphan*/ ) ; 
 int MM_NOP16 ; 
 int SIGBUS ; 
 int access_process_vm (TYPE_3__*,unsigned long,struct emuframe*,int,int) ; 
 int alloc_emuframe () ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/ * dsemul_page () ; 
 int /*<<< orphan*/  errors ; 
 int /*<<< orphan*/  free_emuframe (int,int /*<<< orphan*/ ) ; 
 int get_isa16_mode (int) ; 
 scalar_t__ mm_addiupc_op ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int mips_dsemul(struct pt_regs *regs, mips_instruction ir,
		unsigned long branch_pc, unsigned long cont_pc)
{
	int isa16 = get_isa16_mode(regs->cp0_epc);
	mips_instruction break_math;
	unsigned long fr_uaddr;
	struct emuframe fr;
	int fr_idx, ret;

	/* NOP is easy */
	if (ir == 0)
		return -1;

	/* microMIPS instructions */
	if (isa16) {
		union mips_instruction insn = { .word = ir };

		/* NOP16 aka MOVE16 $0, $0 */
		if ((ir >> 16) == MM_NOP16)
			return -1;

		/* ADDIUPC */
		if (insn.mm_a_format.opcode == mm_addiupc_op) {
			unsigned int rs;
			s32 v;

			rs = (((insn.mm_a_format.rs + 0xe) & 0xf) + 2);
			v = regs->cp0_epc & ~3;
			v += insn.mm_a_format.simmediate << 2;
			regs->regs[rs] = (long)v;
			return -1;
		}
	}

	pr_debug("dsemul 0x%08lx cont at 0x%08lx\n", regs->cp0_epc, cont_pc);

	/* Allocate a frame if we don't already have one */
	fr_idx = atomic_read(&current->thread.bd_emu_frame);
	if (fr_idx == BD_EMUFRAME_NONE)
		fr_idx = alloc_emuframe();
	if (fr_idx == BD_EMUFRAME_NONE)
		return SIGBUS;

	/* Retrieve the appropriately encoded break instruction */
	break_math = BREAK_MATH(isa16);

	/* Write the instructions to the frame */
	if (isa16) {
		union mips_instruction _emul = {
			.halfword = { ir >> 16, ir }
		};
		union mips_instruction _badinst = {
			.halfword = { break_math >> 16, break_math }
		};

		fr.emul = _emul.word;
		fr.badinst = _badinst.word;
	} else {
		fr.emul = ir;
		fr.badinst = break_math;
	}

	/* Write the frame to user memory */
	fr_uaddr = (unsigned long)&dsemul_page()[fr_idx];
	ret = access_process_vm(current, fr_uaddr, &fr, sizeof(fr),
				FOLL_FORCE | FOLL_WRITE);
	if (unlikely(ret != sizeof(fr))) {
		MIPS_FPU_EMU_INC_STATS(errors);
		free_emuframe(fr_idx, current->mm);
		return SIGBUS;
	}

	/* Record the PC of the branch, PC to continue from & frame index */
	current->thread.bd_emu_branch_pc = branch_pc;
	current->thread.bd_emu_cont_pc = cont_pc;
	atomic_set(&current->thread.bd_emu_frame, fr_idx);

	/* Change user register context to execute the frame */
	regs->cp0_epc = fr_uaddr | isa16;

	return 0;
}