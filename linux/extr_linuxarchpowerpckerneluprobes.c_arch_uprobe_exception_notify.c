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
struct notifier_block {int dummy; } ;
struct die_args {struct pt_regs* regs; } ;

/* Variables and functions */
#define  DIE_BPT 129 
#define  DIE_SSTEP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  uprobe_post_sstep_notifier (struct pt_regs*) ; 
 int /*<<< orphan*/  uprobe_pre_sstep_notifier (struct pt_regs*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

int arch_uprobe_exception_notify(struct notifier_block *self,
				unsigned long val, void *data)
{
	struct die_args *args = data;
	struct pt_regs *regs = args->regs;

	/* regs == NULL is a kernel bug */
	if (WARN_ON(!regs))
		return NOTIFY_DONE;

	/* We are only interested in userspace traps */
	if (!user_mode(regs))
		return NOTIFY_DONE;

	switch (val) {
	case DIE_BPT:
		if (uprobe_pre_sstep_notifier(regs))
			return NOTIFY_STOP;
		break;
	case DIE_SSTEP:
		if (uprobe_post_sstep_notifier(regs))
			return NOTIFY_STOP;
	default:
		break;
	}
	return NOTIFY_DONE;
}