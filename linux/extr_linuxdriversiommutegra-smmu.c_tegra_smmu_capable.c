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
typedef  enum iommu_cap { ____Placeholder_iommu_cap } iommu_cap ;

/* Variables and functions */

__attribute__((used)) static bool tegra_smmu_capable(enum iommu_cap cap)
{
	return false;
}