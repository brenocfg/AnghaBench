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
struct amd_iommu {int /*<<< orphan*/ * mmio_base; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int MMIO_DEV_TABLE_OFFSET ; 
 int /*<<< orphan*/  amd_iommu_dev_table ; 
 int dev_table_size ; 
 int iommu_virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void iommu_set_device_table(struct amd_iommu *iommu)
{
	u64 entry;

	BUG_ON(iommu->mmio_base == NULL);

	entry = iommu_virt_to_phys(amd_iommu_dev_table);
	entry |= (dev_table_size >> 12) - 1;
	memcpy_toio(iommu->mmio_base + MMIO_DEV_TABLE_OFFSET,
			&entry, sizeof(entry));
}