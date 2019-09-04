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
struct arm_smmu_device {int /*<<< orphan*/  context_map; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_GR0_NS (struct arm_smmu_device*) ; 
 scalar_t__ ARM_SMMU_GR0_sCR0 ; 
 int /*<<< orphan*/  ARM_SMMU_MAX_CBS ; 
 int ENODEV ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct arm_smmu_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sCR0_CLIENTPD ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int arm_smmu_device_remove(struct platform_device *pdev)
{
	struct arm_smmu_device *smmu = platform_get_drvdata(pdev);

	if (!smmu)
		return -ENODEV;

	if (!bitmap_empty(smmu->context_map, ARM_SMMU_MAX_CBS))
		dev_err(&pdev->dev, "removing device with active domains!\n");

	/* Turn the thing off */
	writel(sCR0_CLIENTPD, ARM_SMMU_GR0_NS(smmu) + ARM_SMMU_GR0_sCR0);
	return 0;
}