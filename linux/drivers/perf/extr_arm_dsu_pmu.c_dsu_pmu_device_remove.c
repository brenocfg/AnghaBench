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
struct dsu_pmu {int /*<<< orphan*/  irq; int /*<<< orphan*/  cpuhp_node; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_state_remove_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsu_pmu_cpuhp_state ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 struct dsu_pmu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dsu_pmu_device_remove(struct platform_device *pdev)
{
	struct dsu_pmu *dsu_pmu = platform_get_drvdata(pdev);

	perf_pmu_unregister(&dsu_pmu->pmu);
	cpuhp_state_remove_instance(dsu_pmu_cpuhp_state, &dsu_pmu->cpuhp_node);
	irq_set_affinity_hint(dsu_pmu->irq, NULL);

	return 0;
}