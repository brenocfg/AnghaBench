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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct arm_smmu_device {int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; int /*<<< orphan*/  dev; int /*<<< orphan*/  context_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_GR0_sCR0 ; 
 int /*<<< orphan*/  ARM_SMMU_MAX_CBS ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_rpm_get (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_rpm_put (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct arm_smmu_device* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ pm_runtime_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sCR0_CLIENTPD ; 

__attribute__((used)) static void arm_smmu_device_shutdown(struct platform_device *pdev)
{
	struct arm_smmu_device *smmu = platform_get_drvdata(pdev);

	if (!smmu)
		return;

	if (!bitmap_empty(smmu->context_map, ARM_SMMU_MAX_CBS))
		dev_err(&pdev->dev, "removing device with active domains!\n");

	arm_smmu_rpm_get(smmu);
	/* Turn the thing off */
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_sCR0, sCR0_CLIENTPD);
	arm_smmu_rpm_put(smmu);

	if (pm_runtime_enabled(smmu->dev))
		pm_runtime_force_suspend(smmu->dev);
	else
		clk_bulk_disable(smmu->num_clks, smmu->clks);

	clk_bulk_unprepare(smmu->num_clks, smmu->clks);
}