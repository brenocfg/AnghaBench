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
struct omap_iommu {int dummy; } ;
struct iotlb_entry {int /*<<< orphan*/  da; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_iotlb_page (struct omap_iommu*,int /*<<< orphan*/ ) ; 
 int iopgtable_store_entry_core (struct omap_iommu*,struct iotlb_entry*) ; 
 int /*<<< orphan*/  prefetch_iotlb_entry (struct omap_iommu*,struct iotlb_entry*) ; 

__attribute__((used)) static int
omap_iopgtable_store_entry(struct omap_iommu *obj, struct iotlb_entry *e)
{
	int err;

	flush_iotlb_page(obj, e->da);
	err = iopgtable_store_entry_core(obj, e);
	if (!err)
		prefetch_iotlb_entry(obj, e);
	return err;
}