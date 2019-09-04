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
struct ldc_iommu {int /*<<< orphan*/  iommu_map_table; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (int) ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  iommu_tbl_range_free (int /*<<< orphan*/ *,int,unsigned long,unsigned long) ; 
 unsigned long ldc_cookie_to_index (int,struct ldc_iommu*) ; 
 int /*<<< orphan*/  ldc_demap (struct ldc_iommu*,unsigned long,int,unsigned long,unsigned long) ; 

__attribute__((used)) static void free_npages(unsigned long id, struct ldc_iommu *iommu,
			u64 cookie, u64 size)
{
	unsigned long npages, entry;

	npages = PAGE_ALIGN(((cookie & ~PAGE_MASK) + size)) >> PAGE_SHIFT;

	entry = ldc_cookie_to_index(cookie, iommu);
	ldc_demap(iommu, id, cookie, entry, npages);
	iommu_tbl_range_free(&iommu->iommu_map_table, cookie, npages, entry);
}