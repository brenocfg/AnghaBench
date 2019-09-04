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
struct iommu_table {int it_offset; int it_page_shift; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 struct iommu_table* get_iommu_table_base (struct device*) ; 

int dma_iommu_dma_supported(struct device *dev, u64 mask)
{
	struct iommu_table *tbl = get_iommu_table_base(dev);

	if (!tbl) {
		dev_info(dev, "Warning: IOMMU dma not supported: mask 0x%08llx"
			", table unavailable\n", mask);
		return 0;
	}

	if (tbl->it_offset > (mask >> tbl->it_page_shift)) {
		dev_info(dev, "Warning: IOMMU offset too big for device mask\n");
		dev_info(dev, "mask: 0x%08llx, table offset: 0x%08lx\n",
				mask, tbl->it_offset << tbl->it_page_shift);
		return 0;
	} else
		return 1;
}