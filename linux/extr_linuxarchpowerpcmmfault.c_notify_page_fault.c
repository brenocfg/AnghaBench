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

/* Variables and functions */
 int /*<<< orphan*/  debugger_fault_handler (struct pt_regs*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool notify_page_fault(struct pt_regs *regs)
{
	bool ret = false;

#ifdef CONFIG_KPROBES
	/* kprobe_running() needs smp_processor_id() */
	if (!user_mode(regs)) {
		preempt_disable();
		if (kprobe_running() && kprobe_fault_handler(regs, 11))
			ret = true;
		preempt_enable();
	}
#endif /* CONFIG_KPROBES */

	if (unlikely(debugger_fault_handler(regs)))
		ret = true;

	return ret;
}