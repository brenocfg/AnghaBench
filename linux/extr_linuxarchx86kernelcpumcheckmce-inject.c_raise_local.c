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
struct mce {int inject_flags; int extcpu; scalar_t__ finished; scalar_t__ status; } ;

/* Variables and functions */
 int EINVAL ; 
 int MCJ_CTX (int) ; 
#define  MCJ_CTX_IRQ 129 
#define  MCJ_CTX_PROCESS 128 
 int MCJ_EXCEPTION ; 
 int /*<<< orphan*/  injectm ; 
 int /*<<< orphan*/  mce_notify_irq () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  raise_exception (struct mce*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raise_poll (struct mce*) ; 
 struct mce* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raise_local(void)
{
	struct mce *m = this_cpu_ptr(&injectm);
	int context = MCJ_CTX(m->inject_flags);
	int ret = 0;
	int cpu = m->extcpu;

	if (m->inject_flags & MCJ_EXCEPTION) {
		pr_info("Triggering MCE exception on CPU %d\n", cpu);
		switch (context) {
		case MCJ_CTX_IRQ:
			/*
			 * Could do more to fake interrupts like
			 * calling irq_enter, but the necessary
			 * machinery isn't exported currently.
			 */
			/*FALL THROUGH*/
		case MCJ_CTX_PROCESS:
			raise_exception(m, NULL);
			break;
		default:
			pr_info("Invalid MCE context\n");
			ret = -EINVAL;
		}
		pr_info("MCE exception done on CPU %d\n", cpu);
	} else if (m->status) {
		pr_info("Starting machine check poll CPU %d\n", cpu);
		raise_poll(m);
		mce_notify_irq();
		pr_info("Machine check poll done on CPU %d\n", cpu);
	} else
		m->finished = 0;

	return ret;
}