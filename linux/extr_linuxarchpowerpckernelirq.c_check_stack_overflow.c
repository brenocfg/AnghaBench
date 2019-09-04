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

/* Variables and functions */

__attribute__((used)) static inline void check_stack_overflow(void)
{
#ifdef CONFIG_DEBUG_STACKOVERFLOW
	long sp;

	sp = current_stack_pointer() & (THREAD_SIZE-1);

	/* check for stack overflow: is there less than 2KB free? */
	if (unlikely(sp < (sizeof(struct thread_info) + 2048))) {
		pr_err("do_IRQ: stack overflow: %ld\n",
			sp - sizeof(struct thread_info));
		dump_stack();
	}
#endif
}