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
struct notifier_block {int dummy; } ;
struct die_args {int /*<<< orphan*/  trapnr; scalar_t__ regs; } ;

/* Variables and functions */
 unsigned long DIE_GPF ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ kprobe_fault_handler (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kprobe_running () ; 
 int /*<<< orphan*/  preemptible () ; 
 scalar_t__ user_mode (scalar_t__) ; 

int kprobe_exceptions_notify(struct notifier_block *self, unsigned long val,
			     void *data)
{
	struct die_args *args = data;
	int ret = NOTIFY_DONE;

	if (args->regs && user_mode(args->regs))
		return ret;

	if (val == DIE_GPF) {
		/*
		 * To be potentially processing a kprobe fault and to
		 * trust the result from kprobe_running(), we have
		 * be non-preemptible.
		 */
		if (!preemptible() && kprobe_running() &&
		    kprobe_fault_handler(args->regs, args->trapnr))
			ret = NOTIFY_STOP;
	}
	return ret;
}