#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_gpu {TYPE_2__* dev; int /*<<< orphan*/  name; } ;
struct msm_gem_address_space {TYPE_4__* mmu; } ;
struct TYPE_5__ {void* aperture_end; void* aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct TYPE_8__ {TYPE_3__* funcs; } ;
struct TYPE_7__ {int (* attach ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct msm_gem_address_space* ERR_CAST (struct msm_gem_address_space*) ; 
 struct msm_gem_address_space* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  PTR_ERR (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct iommu_domain* iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_domain_free (struct iommu_domain*) ; 
 struct msm_gem_address_space* msm_gem_address_space_create (int /*<<< orphan*/ *,struct iommu_domain*,char*) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct msm_gem_address_space *
msm_gpu_create_address_space(struct msm_gpu *gpu, struct platform_device *pdev,
		uint64_t va_start, uint64_t va_end)
{
	struct iommu_domain *iommu;
	struct msm_gem_address_space *aspace;
	int ret;

	/*
	 * Setup IOMMU.. eventually we will (I think) do this once per context
	 * and have separate page tables per context.  For now, to keep things
	 * simple and to get something working, just use a single address space:
	 */
	iommu = iommu_domain_alloc(&platform_bus_type);
	if (!iommu)
		return NULL;

	iommu->geometry.aperture_start = va_start;
	iommu->geometry.aperture_end = va_end;

	dev_info(gpu->dev->dev, "%s: using IOMMU\n", gpu->name);

	aspace = msm_gem_address_space_create(&pdev->dev, iommu, "gpu");
	if (IS_ERR(aspace)) {
		dev_err(gpu->dev->dev, "failed to init iommu: %ld\n",
			PTR_ERR(aspace));
		iommu_domain_free(iommu);
		return ERR_CAST(aspace);
	}

	ret = aspace->mmu->funcs->attach(aspace->mmu, NULL, 0);
	if (ret) {
		msm_gem_address_space_put(aspace);
		return ERR_PTR(ret);
	}

	return aspace;
}