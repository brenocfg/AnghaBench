#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* nodes; } ;
struct TYPE_6__ {int num_cpus; } ;

/* Variables and functions */
 TYPE_2__* build_cpuinfo_tree () ; 
 int /*<<< orphan*/ * cpu_distribution_map ; 
 TYPE_2__* cpuinfo_tree ; 
 int /*<<< orphan*/  iterate_cpu (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void _cpu_map_rebuild(void)
{
	int i;

	if (cpuinfo_tree) {
		kfree(cpuinfo_tree);
		cpuinfo_tree = NULL;
	}

	cpuinfo_tree = build_cpuinfo_tree();
	if (!cpuinfo_tree)
		return;

	/* Build CPU distribution map that spans all online CPUs.  No need
	 * to check if the CPU is online, as that is done when the cpuinfo
	 * tree is being built.
	 */
	for (i = 0; i < cpuinfo_tree->nodes[0].num_cpus; i++)
		cpu_distribution_map[i] = iterate_cpu(cpuinfo_tree, 0);
}