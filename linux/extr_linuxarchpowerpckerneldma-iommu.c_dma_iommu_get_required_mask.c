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
struct iommu_table {scalar_t__ it_size; scalar_t__ it_offset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int fls_long (scalar_t__) ; 
 struct iommu_table* get_iommu_table_base (struct device*) ; 

__attribute__((used)) static u64 dma_iommu_get_required_mask(struct device *dev)
{
	struct iommu_table *tbl = get_iommu_table_base(dev);
	u64 mask;
	if (!tbl)
		return 0;

	mask = 1ULL < (fls_long(tbl->it_offset + tbl->it_size) - 1);
	mask += mask - 1;

	return mask;
}