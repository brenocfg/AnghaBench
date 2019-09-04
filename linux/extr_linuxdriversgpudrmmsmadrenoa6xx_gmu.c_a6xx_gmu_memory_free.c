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
typedef  int /*<<< orphan*/  u64 ;
struct a6xx_gmu_bo {int size; struct a6xx_gmu_bo* pages; int /*<<< orphan*/  iova; } ;
struct a6xx_gmu {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct a6xx_gmu_bo*) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (struct a6xx_gmu_bo,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct a6xx_gmu_bo*) ; 

__attribute__((used)) static void a6xx_gmu_memory_free(struct a6xx_gmu *gmu, struct a6xx_gmu_bo *bo)
{
	int count, i;
	u64 iova;

	if (IS_ERR_OR_NULL(bo))
		return;

	count = bo->size >> PAGE_SHIFT;
	iova = bo->iova;

	for (i = 0; i < count; i++, iova += PAGE_SIZE) {
		iommu_unmap(gmu->domain, iova, PAGE_SIZE);
		__free_pages(bo->pages[i], 0);
	}

	kfree(bo->pages);
	kfree(bo);
}