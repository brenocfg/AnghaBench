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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 int total_cpus ; 

__attribute__((used)) static ssize_t print_cpus_offline(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	int n = 0, len = PAGE_SIZE-2;
	cpumask_var_t offline;

	/* display offline cpus < nr_cpu_ids */
	if (!alloc_cpumask_var(&offline, GFP_KERNEL))
		return -ENOMEM;
	cpumask_andnot(offline, cpu_possible_mask, cpu_online_mask);
	n = scnprintf(buf, len, "%*pbl", cpumask_pr_args(offline));
	free_cpumask_var(offline);

	/* display offline cpus >= nr_cpu_ids */
	if (total_cpus && nr_cpu_ids < total_cpus) {
		if (n && n < len)
			buf[n++] = ',';

		if (nr_cpu_ids == total_cpus-1)
			n += snprintf(&buf[n], len - n, "%u", nr_cpu_ids);
		else
			n += snprintf(&buf[n], len - n, "%u-%d",
						      nr_cpu_ids, total_cpus-1);
	}

	n += snprintf(&buf[n], len - n, "\n");
	return n;
}