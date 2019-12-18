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
struct xgene_pmu {int /*<<< orphan*/  node; int /*<<< orphan*/  mcpmus; int /*<<< orphan*/  mcbpmus; int /*<<< orphan*/  iobpmus; int /*<<< orphan*/  l3cpmus; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct xgene_pmu* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_pmu_dev_cleanup (struct xgene_pmu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xgene_pmu_remove(struct platform_device *pdev)
{
	struct xgene_pmu *xgene_pmu = dev_get_drvdata(&pdev->dev);

	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->l3cpmus);
	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->iobpmus);
	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->mcbpmus);
	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->mcpmus);
	cpuhp_state_remove_instance(CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE,
				    &xgene_pmu->node);

	return 0;
}