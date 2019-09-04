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
struct intel_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DOMAIN_ADDRESS_WIDTH ; 
 int __iommu_calculate_agaw (struct intel_iommu*,int /*<<< orphan*/ ) ; 

int iommu_calculate_agaw(struct intel_iommu *iommu)
{
	return __iommu_calculate_agaw(iommu, DEFAULT_DOMAIN_ADDRESS_WIDTH);
}