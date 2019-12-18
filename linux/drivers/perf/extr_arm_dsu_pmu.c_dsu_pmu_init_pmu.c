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
struct dsu_pmu {int num_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsu_pmu_get_reset_overflow () ; 
 int /*<<< orphan*/  dsu_pmu_probe_pmu (struct dsu_pmu*) ; 

__attribute__((used)) static void dsu_pmu_init_pmu(struct dsu_pmu *dsu_pmu)
{
	if (dsu_pmu->num_counters == -1)
		dsu_pmu_probe_pmu(dsu_pmu);
	/* Reset the interrupt overflow mask */
	dsu_pmu_get_reset_overflow();
}