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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {unsigned int* insn; int boostable; } ;
struct kprobe {TYPE_1__ ainsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int emulate_step (struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int try_to_emulate(struct kprobe *p, struct pt_regs *regs)
{
	int ret;
	unsigned int insn = *p->ainsn.insn;

	/* regs->nip is also adjusted if emulate_step returns 1 */
	ret = emulate_step(regs, insn);
	if (ret > 0) {
		/*
		 * Once this instruction has been boosted
		 * successfully, set the boostable flag
		 */
		if (unlikely(p->ainsn.boostable == 0))
			p->ainsn.boostable = 1;
	} else if (ret < 0) {
		/*
		 * We don't allow kprobes on mtmsr(d)/rfi(d), etc.
		 * So, we should never get here... but, its still
		 * good to catch them, just in case...
		 */
		printk("Can't step on instruction %x\n", insn);
		BUG();
	} else {
		/*
		 * If we haven't previously emulated this instruction, then it
		 * can't be boosted. Note it down so we don't try to do so again.
		 *
		 * If, however, we had emulated this instruction in the past,
		 * then this is just an error with the current run (for
		 * instance, exceptions due to a load/store). We return 0 so
		 * that this is now single-stepped, but continue to try
		 * emulating it in subsequent probe hits.
		 */
		if (unlikely(p->ainsn.boostable != 1))
			p->ainsn.boostable = -1;
	}

	return ret;
}