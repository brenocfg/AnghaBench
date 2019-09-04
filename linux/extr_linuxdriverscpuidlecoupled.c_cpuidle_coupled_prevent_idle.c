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
struct cpuidle_coupled {int /*<<< orphan*/  prevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpuidle_coupled_no_cpus_waiting (struct cpuidle_coupled*) ; 
 int /*<<< orphan*/  cpuidle_coupled_poke_others (int,struct cpuidle_coupled*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static void cpuidle_coupled_prevent_idle(struct cpuidle_coupled *coupled)
{
	int cpu = get_cpu();

	/* Force all cpus out of the waiting loop. */
	coupled->prevent++;
	cpuidle_coupled_poke_others(cpu, coupled);
	put_cpu();
	while (!cpuidle_coupled_no_cpus_waiting(coupled))
		cpu_relax();
}