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
typedef  scalar_t__ u32 ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_TABLE_ENTRIES ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_flush_irt (struct amd_iommu*,scalar_t__) ; 

__attribute__((used)) static void amd_iommu_flush_irt_all(struct amd_iommu *iommu)
{
	u32 devid;

	for (devid = 0; devid <= MAX_DEV_TABLE_ENTRIES; devid++)
		iommu_flush_irt(iommu, devid);

	iommu_completion_wait(iommu);
}