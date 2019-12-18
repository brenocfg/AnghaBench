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
struct smmu_pmu {int /*<<< orphan*/  pmu; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct smmu_pmu* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  smmu_pmu_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smmu_pmu_shutdown(struct platform_device *pdev)
{
	struct smmu_pmu *smmu_pmu = platform_get_drvdata(pdev);

	smmu_pmu_disable(&smmu_pmu->pmu);
}