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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int aperture_end; int force_aperture; scalar_t__ aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct tegra_smmu_as {int attr; struct iommu_domain domain; int /*<<< orphan*/  pd; struct tegra_smmu_as* count; void* pts; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 int /*<<< orphan*/  SMMU_NUM_PDE ; 
 int SMMU_PD_NONSECURE ; 
 int SMMU_PD_READABLE ; 
 int SMMU_PD_WRITABLE ; 
 int __GFP_DMA ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_page (int) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct tegra_smmu_as*) ; 
 struct tegra_smmu_as* kzalloc (int,int) ; 

__attribute__((used)) static struct iommu_domain *tegra_smmu_domain_alloc(unsigned type)
{
	struct tegra_smmu_as *as;

	if (type != IOMMU_DOMAIN_UNMANAGED)
		return NULL;

	as = kzalloc(sizeof(*as), GFP_KERNEL);
	if (!as)
		return NULL;

	as->attr = SMMU_PD_READABLE | SMMU_PD_WRITABLE | SMMU_PD_NONSECURE;

	as->pd = alloc_page(GFP_KERNEL | __GFP_DMA | __GFP_ZERO);
	if (!as->pd) {
		kfree(as);
		return NULL;
	}

	as->count = kcalloc(SMMU_NUM_PDE, sizeof(u32), GFP_KERNEL);
	if (!as->count) {
		__free_page(as->pd);
		kfree(as);
		return NULL;
	}

	as->pts = kcalloc(SMMU_NUM_PDE, sizeof(*as->pts), GFP_KERNEL);
	if (!as->pts) {
		kfree(as->count);
		__free_page(as->pd);
		kfree(as);
		return NULL;
	}

	/* setup aperture */
	as->domain.geometry.aperture_start = 0;
	as->domain.geometry.aperture_end = 0xffffffff;
	as->domain.geometry.force_aperture = true;

	return &as->domain;
}