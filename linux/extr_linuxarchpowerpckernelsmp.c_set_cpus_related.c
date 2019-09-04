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
 int /*<<< orphan*/  cpumask_set_cpu (int,struct cpumask*) ; 

__attribute__((used)) static void set_cpus_related(int i, int j, struct cpumask *(*get_cpumask)(int))
{
	cpumask_set_cpu(i, get_cpumask(j));
	cpumask_set_cpu(j, get_cpumask(i));
}