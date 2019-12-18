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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct malidp_plane {TYPE_2__ base; } ;
struct iommu_domain {int /*<<< orphan*/  pgsize_bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct iommu_domain* iommu_get_domain_for_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 

__attribute__((used)) static u32 malidp_get_pgsize_bitmap(struct malidp_plane *mp)
{
	u32 pgsize_bitmap = 0;

	if (iommu_present(&platform_bus_type)) {
		struct iommu_domain *mmu_dom =
			iommu_get_domain_for_dev(mp->base.dev->dev);

		if (mmu_dom)
			pgsize_bitmap = mmu_dom->pgsize_bitmap;
	}

	return pgsize_bitmap;
}