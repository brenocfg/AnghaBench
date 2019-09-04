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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int alloc_init_cpu_groups (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumap_print_to_pagebuf (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ down_and_up_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpu_groups (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int hotplug_tests(void)
{
	int i, nb_cpu_group, err = -ENOMEM;
	cpumask_var_t offlined_cpus, *cpu_groups;
	char *page_buf;

	if (!alloc_cpumask_var(&offlined_cpus, GFP_KERNEL))
		return err;

	nb_cpu_group = alloc_init_cpu_groups(&cpu_groups);
	if (nb_cpu_group < 0)
		goto out_free_cpus;
	page_buf = (char *)__get_free_page(GFP_KERNEL);
	if (!page_buf)
		goto out_free_cpu_groups;

	err = 0;
	/*
	 * Of course the last CPU cannot be powered down and cpu_down() should
	 * refuse doing that.
	 */
	pr_info("Trying to turn off and on again all CPUs\n");
	err += down_and_up_cpus(cpu_online_mask, offlined_cpus);

	/*
	 * Take down CPUs by cpu group this time. When the last CPU is turned
	 * off, the cpu group itself should shut down.
	 */
	for (i = 0; i < nb_cpu_group; ++i) {
		ssize_t len = cpumap_print_to_pagebuf(true, page_buf,
						      cpu_groups[i]);
		/* Remove trailing newline. */
		page_buf[len - 1] = '\0';
		pr_info("Trying to turn off and on again group %d (CPUs %s)\n",
			i, page_buf);
		err += down_and_up_cpus(cpu_groups[i], offlined_cpus);
	}

	free_page((unsigned long)page_buf);
out_free_cpu_groups:
	free_cpu_groups(nb_cpu_group, &cpu_groups);
out_free_cpus:
	free_cpumask_var(offlined_cpus);
	return err;
}