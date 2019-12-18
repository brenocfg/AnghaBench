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
typedef  int u64 ;
struct amd_iommu {int exclusion_start; int exclusion_length; scalar_t__ mmio_base; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 scalar_t__ MMIO_EXCL_BASE_OFFSET ; 
 int MMIO_EXCL_ENABLE_MASK ; 
 scalar_t__ MMIO_EXCL_LIMIT_OFFSET ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int*,int) ; 

__attribute__((used)) static void iommu_set_exclusion_range(struct amd_iommu *iommu)
{
	u64 start = iommu->exclusion_start & PAGE_MASK;
	u64 limit = (start + iommu->exclusion_length - 1) & PAGE_MASK;
	u64 entry;

	if (!iommu->exclusion_start)
		return;

	entry = start | MMIO_EXCL_ENABLE_MASK;
	memcpy_toio(iommu->mmio_base + MMIO_EXCL_BASE_OFFSET,
			&entry, sizeof(entry));

	entry = limit;
	memcpy_toio(iommu->mmio_base + MMIO_EXCL_LIMIT_OFFSET,
			&entry, sizeof(entry));
}