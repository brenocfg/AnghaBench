#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_CCI_ONLINE ; 
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_cci_pmu ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cci_pmu_remove(struct platform_device *pdev)
{
	if (!g_cci_pmu)
		return 0;

	cpuhp_remove_state(CPUHP_AP_PERF_ARM_CCI_ONLINE);
	perf_pmu_unregister(&g_cci_pmu->pmu);
	g_cci_pmu = NULL;

	return 0;
}