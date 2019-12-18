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
struct arm_smmu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ pm_runtime_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void arm_smmu_rpm_put(struct arm_smmu_device *smmu)
{
	if (pm_runtime_enabled(smmu->dev))
		pm_runtime_put(smmu->dev);
}