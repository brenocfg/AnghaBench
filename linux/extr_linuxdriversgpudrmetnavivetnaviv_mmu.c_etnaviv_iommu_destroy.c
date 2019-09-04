#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_iommu {TYPE_2__* domain; int /*<<< orphan*/  mm; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommu*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void etnaviv_iommu_destroy(struct etnaviv_iommu *mmu)
{
	drm_mm_takedown(&mmu->mm);
	mmu->domain->ops->free(mmu->domain);
	kfree(mmu);
}