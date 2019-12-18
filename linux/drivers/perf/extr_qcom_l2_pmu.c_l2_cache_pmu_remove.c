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
struct platform_device {int dummy; } ;
struct l2cache_pmu {int /*<<< orphan*/  node; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 struct l2cache_pmu* to_l2cache_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2_cache_pmu_remove(struct platform_device *pdev)
{
	struct l2cache_pmu *l2cache_pmu =
		to_l2cache_pmu(platform_get_drvdata(pdev));

	perf_pmu_unregister(&l2cache_pmu->pmu);
	cpuhp_state_remove_instance(CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE,
				    &l2cache_pmu->node);
	return 0;
}