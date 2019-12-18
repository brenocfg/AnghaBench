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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int of_count_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_cpu_node_to_id (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 

__attribute__((used)) static int dsu_pmu_dt_get_cpus(struct device_node *dev, cpumask_t *mask)
{
	int i = 0, n, cpu;
	struct device_node *cpu_node;

	n = of_count_phandle_with_args(dev, "cpus", NULL);
	if (n <= 0)
		return -ENODEV;
	for (; i < n; i++) {
		cpu_node = of_parse_phandle(dev, "cpus", i);
		if (!cpu_node)
			break;
		cpu = of_cpu_node_to_id(cpu_node);
		of_node_put(cpu_node);
		/*
		 * We have to ignore the failures here and continue scanning
		 * the list to handle cases where the nr_cpus could be capped
		 * in the running kernel.
		 */
		if (cpu < 0)
			continue;
		cpumask_set_cpu(cpu, mask);
	}
	return 0;
}