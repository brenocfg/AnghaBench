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
 int /*<<< orphan*/  cpuidle_coupled_poke_pending ; 
 int /*<<< orphan*/  cpuidle_coupled_poked ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuidle_coupled_handle_poke(void *info)
{
	int cpu = (unsigned long)info;
	cpumask_set_cpu(cpu, &cpuidle_coupled_poked);
	cpumask_clear_cpu(cpu, &cpuidle_coupled_poke_pending);
}