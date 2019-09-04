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
struct intel_iommu {int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 unsigned long cap_sagaw (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 int width_to_agaw (int) ; 

__attribute__((used)) static int __iommu_calculate_agaw(struct intel_iommu *iommu, int max_gaw)
{
	unsigned long sagaw;
	int agaw = -1;

	sagaw = cap_sagaw(iommu->cap);
	for (agaw = width_to_agaw(max_gaw);
	     agaw >= 0; agaw--) {
		if (test_bit(agaw, &sagaw))
			break;
	}

	return agaw;
}