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
struct cpu_hw_events {int /*<<< orphan*/  active_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_enable_all (int) ; 
 int /*<<< orphan*/  intel_set_tfa (struct cpu_hw_events*,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_tfa_pmu_enable_all(int added)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * If we find PMC3 is no longer used when we enable the PMU, we can
	 * clear TFA.
	 */
	if (!test_bit(3, cpuc->active_mask))
		intel_set_tfa(cpuc, false);

	intel_pmu_enable_all(added);
}