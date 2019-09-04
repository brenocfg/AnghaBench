#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mm; } ;
struct etnaviv_vram_mapping {int /*<<< orphan*/  mmu_node; TYPE_1__ vram_node; int /*<<< orphan*/  use; } ;
struct etnaviv_iommu {int need_flush; int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_iommu_remove_mapping (struct etnaviv_iommu*,struct etnaviv_vram_mapping*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void etnaviv_iommu_unmap_gem(struct etnaviv_iommu *mmu,
	struct etnaviv_vram_mapping *mapping)
{
	WARN_ON(mapping->use);

	mutex_lock(&mmu->lock);

	/* If the vram node is on the mm, unmap and remove the node */
	if (mapping->vram_node.mm == &mmu->mm)
		etnaviv_iommu_remove_mapping(mmu, mapping);

	list_del(&mapping->mmu_node);
	mmu->need_flush = true;
	mutex_unlock(&mmu->lock);
}