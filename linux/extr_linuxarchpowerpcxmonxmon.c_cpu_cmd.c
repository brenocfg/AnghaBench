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

__attribute__((used)) static int cpu_cmd(void)
{
#ifdef CONFIG_SMP
	unsigned long cpu, first_cpu, last_cpu;
	int timeout;

	if (!scanhex(&cpu)) {
		/* print cpus waiting or in xmon */
		printf("cpus stopped:");
		last_cpu = first_cpu = NR_CPUS;
		for_each_possible_cpu(cpu) {
			if (cpumask_test_cpu(cpu, &cpus_in_xmon)) {
				if (cpu == last_cpu + 1) {
					last_cpu = cpu;
				} else {
					if (last_cpu != first_cpu)
						printf("-0x%lx", last_cpu);
					last_cpu = first_cpu = cpu;
					printf(" 0x%lx", cpu);
				}
			}
		}
		if (last_cpu != first_cpu)
			printf("-0x%lx", last_cpu);
		printf("\n");
		return 0;
	}
	/* try to switch to cpu specified */
	if (!cpumask_test_cpu(cpu, &cpus_in_xmon)) {
		printf("cpu 0x%lx isn't in xmon\n", cpu);
#ifdef CONFIG_PPC64
		printf("backtrace of paca[0x%lx].saved_r1 (possibly stale):\n", cpu);
		xmon_show_stack(paca_ptrs[cpu]->saved_r1, 0, 0);
#endif
		return 0;
	}
	xmon_taken = 0;
	mb();
	xmon_owner = cpu;
	timeout = 10000000;
	while (!xmon_taken) {
		if (--timeout == 0) {
			if (test_and_set_bit(0, &xmon_taken))
				break;
			/* take control back */
			mb();
			xmon_owner = smp_processor_id();
			printf("cpu 0x%lx didn't take control\n", cpu);
			return 0;
		}
		barrier();
	}
	return 1;
#else
	return 0;
#endif /* CONFIG_SMP */
}