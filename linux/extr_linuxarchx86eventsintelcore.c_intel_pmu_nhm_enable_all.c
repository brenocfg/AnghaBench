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
 int /*<<< orphan*/  intel_pmu_enable_all (int) ; 
 int /*<<< orphan*/  intel_pmu_nhm_workaround () ; 

__attribute__((used)) static void intel_pmu_nhm_enable_all(int added)
{
	if (added)
		intel_pmu_nhm_workaround();
	intel_pmu_enable_all(added);
}