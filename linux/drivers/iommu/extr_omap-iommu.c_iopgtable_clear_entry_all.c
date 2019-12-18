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
typedef  int u32 ;
struct omap_iommu {int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  pd_dma; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 int IOPGD_SHIFT ; 
 int PTRS_PER_IOPGD ; 
 int /*<<< orphan*/  flush_iopte_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  flush_iotlb_all (struct omap_iommu*) ; 
 int iopgd_index (int) ; 
 scalar_t__ iopgd_is_table (int) ; 
 int* iopgd_offset (struct omap_iommu*,int) ; 
 int /*<<< orphan*/  iopte_free (struct omap_iommu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iopte_offset (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iopgtable_clear_entry_all(struct omap_iommu *obj)
{
	unsigned long offset;
	int i;

	spin_lock(&obj->page_table_lock);

	for (i = 0; i < PTRS_PER_IOPGD; i++) {
		u32 da;
		u32 *iopgd;

		da = i << IOPGD_SHIFT;
		iopgd = iopgd_offset(obj, da);
		offset = iopgd_index(da) * sizeof(da);

		if (!*iopgd)
			continue;

		if (iopgd_is_table(*iopgd))
			iopte_free(obj, iopte_offset(iopgd, 0), true);

		*iopgd = 0;
		flush_iopte_range(obj->dev, obj->pd_dma, offset, 1);
	}

	flush_iotlb_all(obj);

	spin_unlock(&obj->page_table_lock);
}