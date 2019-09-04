#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct etnaviv_iommu {int version; TYPE_2__* domain; int /*<<< orphan*/  mm; int /*<<< orphan*/  mappings; int /*<<< orphan*/  lock; struct etnaviv_gpu* gpu; } ;
struct TYPE_4__ {int minor_features1; } ;
struct etnaviv_gpu {int /*<<< orphan*/  dev; TYPE_1__ identity; } ;
typedef  enum etnaviv_iommu_version { ____Placeholder_etnaviv_iommu_version } etnaviv_iommu_version ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct etnaviv_iommu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int ETNAVIV_IOMMU_V1 ; 
 int ETNAVIV_IOMMU_V2 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int chipMinorFeatures1_MMU_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* etnaviv_iommuv1_domain_alloc (struct etnaviv_gpu*) ; 
 TYPE_2__* etnaviv_iommuv2_domain_alloc (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommu*) ; 
 struct etnaviv_iommu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct etnaviv_iommu *etnaviv_iommu_new(struct etnaviv_gpu *gpu)
{
	enum etnaviv_iommu_version version;
	struct etnaviv_iommu *mmu;

	mmu = kzalloc(sizeof(*mmu), GFP_KERNEL);
	if (!mmu)
		return ERR_PTR(-ENOMEM);

	if (!(gpu->identity.minor_features1 & chipMinorFeatures1_MMU_VERSION)) {
		mmu->domain = etnaviv_iommuv1_domain_alloc(gpu);
		version = ETNAVIV_IOMMU_V1;
	} else {
		mmu->domain = etnaviv_iommuv2_domain_alloc(gpu);
		version = ETNAVIV_IOMMU_V2;
	}

	if (!mmu->domain) {
		dev_err(gpu->dev, "Failed to allocate GPU IOMMU domain\n");
		kfree(mmu);
		return ERR_PTR(-ENOMEM);
	}

	mmu->gpu = gpu;
	mmu->version = version;
	mutex_init(&mmu->lock);
	INIT_LIST_HEAD(&mmu->mappings);

	drm_mm_init(&mmu->mm, mmu->domain->base, mmu->domain->size);

	return mmu;
}