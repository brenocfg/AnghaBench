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
struct pt_regs {int /*<<< orphan*/  msr; scalar_t__ nip; } ;
struct kprobe_ctlblk {scalar_t__ kprobe_status; int /*<<< orphan*/  kprobe_saved_msr; } ;
struct TYPE_2__ {unsigned int* insn; scalar_t__ boostable; } ;
struct kprobe {int /*<<< orphan*/  (* post_handler ) (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ;TYPE_1__ ainsn; scalar_t__ (* pre_handler ) (struct kprobe*,struct pt_regs*) ;} ;
typedef  unsigned int kprobe_opcode_t ;

/* Variables and functions */
 unsigned int BREAKPOINT_INSTRUCTION ; 
 scalar_t__ KPROBE_HIT_ACTIVE ; 
 scalar_t__ KPROBE_HIT_SS ; 
 scalar_t__ KPROBE_HIT_SSDONE ; 
 scalar_t__ KPROBE_REENTER ; 
 int /*<<< orphan*/  MSR_SINGLESTEP ; 
 struct kprobe* get_kprobe (unsigned int*) ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 scalar_t__ is_trap (unsigned int) ; 
 scalar_t__ kprobe_running () ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (struct kprobe*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  prepare_singlestep (struct kprobe*,struct pt_regs*) ; 
 int /*<<< orphan*/  reset_current_kprobe () ; 
 int /*<<< orphan*/  restore_previous_kprobe (struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  save_previous_kprobe (struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  set_current_kprobe (struct kprobe*,struct pt_regs*,struct kprobe_ctlblk*) ; 
 scalar_t__ stub1 (struct kprobe*,struct pt_regs*) ; 
 int /*<<< orphan*/  stub2 (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int try_to_emulate (struct kprobe*,struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int kprobe_handler(struct pt_regs *regs)
{
	struct kprobe *p;
	int ret = 0;
	unsigned int *addr = (unsigned int *)regs->nip;
	struct kprobe_ctlblk *kcb;

	if (user_mode(regs))
		return 0;

	/*
	 * We don't want to be preempted for the entire
	 * duration of kprobe processing
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();

	/* Check we're not actually recursing */
	if (kprobe_running()) {
		p = get_kprobe(addr);
		if (p) {
			kprobe_opcode_t insn = *p->ainsn.insn;
			if (kcb->kprobe_status == KPROBE_HIT_SS &&
					is_trap(insn)) {
				/* Turn off 'trace' bits */
				regs->msr &= ~MSR_SINGLESTEP;
				regs->msr |= kcb->kprobe_saved_msr;
				goto no_kprobe;
			}
			/* We have reentered the kprobe_handler(), since
			 * another probe was hit while within the handler.
			 * We here save the original kprobes variables and
			 * just single step on the instruction of the new probe
			 * without calling any user handlers.
			 */
			save_previous_kprobe(kcb);
			set_current_kprobe(p, regs, kcb);
			kprobes_inc_nmissed_count(p);
			kcb->kprobe_status = KPROBE_REENTER;
			if (p->ainsn.boostable >= 0) {
				ret = try_to_emulate(p, regs);

				if (ret > 0) {
					restore_previous_kprobe(kcb);
					preempt_enable_no_resched();
					return 1;
				}
			}
			prepare_singlestep(p, regs);
			return 1;
		} else if (*addr != BREAKPOINT_INSTRUCTION) {
			/* If trap variant, then it belongs not to us */
			kprobe_opcode_t cur_insn = *addr;

			if (is_trap(cur_insn))
				goto no_kprobe;
			/* The breakpoint instruction was removed by
			 * another cpu right after we hit, no further
			 * handling of this interrupt is appropriate
			 */
			ret = 1;
		}
		goto no_kprobe;
	}

	p = get_kprobe(addr);
	if (!p) {
		if (*addr != BREAKPOINT_INSTRUCTION) {
			/*
			 * PowerPC has multiple variants of the "trap"
			 * instruction. If the current instruction is a
			 * trap variant, it could belong to someone else
			 */
			kprobe_opcode_t cur_insn = *addr;
			if (is_trap(cur_insn))
				goto no_kprobe;
			/*
			 * The breakpoint instruction was removed right
			 * after we hit it.  Another cpu has removed
			 * either a probepoint or a debugger breakpoint
			 * at this address.  In either case, no further
			 * handling of this interrupt is appropriate.
			 */
			ret = 1;
		}
		/* Not one of ours: let kernel handle it */
		goto no_kprobe;
	}

	kcb->kprobe_status = KPROBE_HIT_ACTIVE;
	set_current_kprobe(p, regs, kcb);
	if (p->pre_handler && p->pre_handler(p, regs)) {
		/* handler changed execution path, so skip ss setup */
		reset_current_kprobe();
		preempt_enable_no_resched();
		return 1;
	}

	if (p->ainsn.boostable >= 0) {
		ret = try_to_emulate(p, regs);

		if (ret > 0) {
			if (p->post_handler)
				p->post_handler(p, regs, 0);

			kcb->kprobe_status = KPROBE_HIT_SSDONE;
			reset_current_kprobe();
			preempt_enable_no_resched();
			return 1;
		}
	}
	prepare_singlestep(p, regs);
	kcb->kprobe_status = KPROBE_HIT_SS;
	return 1;

no_kprobe:
	preempt_enable_no_resched();
	return ret;
}