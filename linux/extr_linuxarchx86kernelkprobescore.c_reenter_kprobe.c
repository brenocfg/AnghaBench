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
struct pt_regs {int dummy; } ;
struct kprobe_ctlblk {int kprobe_status; } ;
struct kprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  KPROBE_HIT_ACTIVE 131 
#define  KPROBE_HIT_SS 130 
#define  KPROBE_HIT_SSDONE 129 
#define  KPROBE_REENTER 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dump_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (struct kprobe*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  setup_singlestep (struct kprobe*,struct pt_regs*,struct kprobe_ctlblk*,int) ; 

__attribute__((used)) static int reenter_kprobe(struct kprobe *p, struct pt_regs *regs,
			  struct kprobe_ctlblk *kcb)
{
	switch (kcb->kprobe_status) {
	case KPROBE_HIT_SSDONE:
	case KPROBE_HIT_ACTIVE:
	case KPROBE_HIT_SS:
		kprobes_inc_nmissed_count(p);
		setup_singlestep(p, regs, kcb, 1);
		break;
	case KPROBE_REENTER:
		/* A probe has been hit in the codepath leading up to, or just
		 * after, single-stepping of a probed instruction. This entire
		 * codepath should strictly reside in .kprobes.text section.
		 * Raise a BUG or we'll continue in an endless reentering loop
		 * and eventually a stack overflow.
		 */
		pr_err("Unrecoverable kprobe detected.\n");
		dump_kprobe(p);
		BUG();
	default:
		/* impossible cases */
		WARN_ON(1);
		return 0;
	}

	return 1;
}