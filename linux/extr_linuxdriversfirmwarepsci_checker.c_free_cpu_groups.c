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
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_cpu_groups(int num, cpumask_var_t **pcpu_groups)
{
	int i;
	cpumask_var_t *cpu_groups = *pcpu_groups;

	for (i = 0; i < num; ++i)
		free_cpumask_var(cpu_groups[i]);
	kfree(cpu_groups);
}