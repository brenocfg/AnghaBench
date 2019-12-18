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
struct ddr_pmu {int /*<<< orphan*/  id; int /*<<< orphan*/  pmu; int /*<<< orphan*/  irq; int /*<<< orphan*/  node; int /*<<< orphan*/  cpuhp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddr_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 struct ddr_pmu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ddr_perf_remove(struct platform_device *pdev)
{
	struct ddr_pmu *pmu = platform_get_drvdata(pdev);

	cpuhp_state_remove_instance_nocalls(pmu->cpuhp_state, &pmu->node);
	irq_set_affinity_hint(pmu->irq, NULL);

	perf_pmu_unregister(&pmu->pmu);

	ida_simple_remove(&ddr_ida, pmu->id);
	return 0;
}