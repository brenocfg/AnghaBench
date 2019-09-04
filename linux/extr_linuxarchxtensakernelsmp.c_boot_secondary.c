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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cpu_start_ccount ; 
 unsigned long get_ccount () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mx_cpu_start ; 
 int /*<<< orphan*/  mx_cpu_stop ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int boot_secondary(unsigned int cpu, struct task_struct *ts)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	unsigned long ccount;
	int i;

#ifdef CONFIG_HOTPLUG_CPU
	WRITE_ONCE(cpu_start_id, cpu);
	/* Pairs with the third memw in the cpu_restart */
	mb();
	system_flush_invalidate_dcache_range((unsigned long)&cpu_start_id,
					     sizeof(cpu_start_id));
#endif
	smp_call_function_single(0, mx_cpu_start, (void *)cpu, 1);

	for (i = 0; i < 2; ++i) {
		do
			ccount = get_ccount();
		while (!ccount);

		WRITE_ONCE(cpu_start_ccount, ccount);

		do {
			/*
			 * Pairs with the first two memws in the
			 * .Lboot_secondary.
			 */
			mb();
			ccount = READ_ONCE(cpu_start_ccount);
		} while (ccount && time_before(jiffies, timeout));

		if (ccount) {
			smp_call_function_single(0, mx_cpu_stop,
						 (void *)cpu, 1);
			WRITE_ONCE(cpu_start_ccount, 0);
			return -EIO;
		}
	}
	return 0;
}