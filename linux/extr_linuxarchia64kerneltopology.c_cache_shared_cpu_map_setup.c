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
struct cache_info {int /*<<< orphan*/  shared_cpu_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_shared_cpu_map_setup(unsigned int cpu,
		struct cache_info * this_leaf)
{
	cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
	return;
}