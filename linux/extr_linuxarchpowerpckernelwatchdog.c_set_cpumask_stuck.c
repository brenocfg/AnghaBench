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
typedef  int /*<<< orphan*/  u64 ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cpumask const*) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_or (struct cpumask const*,struct cpumask const*,struct cpumask const*) ; 
 int /*<<< orphan*/  wd_cpus_enabled ; 
 int /*<<< orphan*/  wd_smp_cpus_pending ; 
 struct cpumask const wd_smp_cpus_stuck ; 
 int /*<<< orphan*/  wd_smp_last_reset_tb ; 

__attribute__((used)) static void set_cpumask_stuck(const struct cpumask *cpumask, u64 tb)
{
	cpumask_or(&wd_smp_cpus_stuck, &wd_smp_cpus_stuck, cpumask);
	cpumask_andnot(&wd_smp_cpus_pending, &wd_smp_cpus_pending, cpumask);
	if (cpumask_empty(&wd_smp_cpus_pending)) {
		wd_smp_last_reset_tb = tb;
		cpumask_andnot(&wd_smp_cpus_pending,
				&wd_cpus_enabled,
				&wd_smp_cpus_stuck);
	}
}