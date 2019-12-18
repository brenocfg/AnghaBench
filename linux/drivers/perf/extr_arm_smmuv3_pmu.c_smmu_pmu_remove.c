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
struct smmu_pmu {int /*<<< orphan*/  node; int /*<<< orphan*/  pmu; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_state_num ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 struct smmu_pmu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int smmu_pmu_remove(struct platform_device *pdev)
{
	struct smmu_pmu *smmu_pmu = platform_get_drvdata(pdev);

	perf_pmu_unregister(&smmu_pmu->pmu);
	cpuhp_state_remove_instance_nocalls(cpuhp_state_num, &smmu_pmu->node);

	return 0;
}