#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msm_gem_address_space {TYPE_5__* mmu; } ;
struct TYPE_6__ {int aperture_start; int aperture_end; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct TYPE_9__ {struct msm_gem_address_space* aspace; } ;
struct dpu_kms {TYPE_4__ base; TYPE_2__* dev; } ;
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_8__ {int (* attach ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 scalar_t__ IS_ERR (struct msm_gem_address_space*) ; 
 int PTR_ERR (struct msm_gem_address_space*) ; 
 struct iommu_domain* iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_domain_free (struct iommu_domain*) ; 
 int /*<<< orphan*/  iommu_ports ; 
 struct msm_gem_address_space* msm_gem_address_space_create (int /*<<< orphan*/ ,struct iommu_domain*,char*) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_kms_mmu_init(struct dpu_kms *dpu_kms)
{
	struct iommu_domain *domain;
	struct msm_gem_address_space *aspace;
	int ret;

	domain = iommu_domain_alloc(&platform_bus_type);
	if (!domain)
		return 0;

	domain->geometry.aperture_start = 0x1000;
	domain->geometry.aperture_end = 0xffffffff;

	aspace = msm_gem_address_space_create(dpu_kms->dev->dev,
			domain, "dpu1");
	if (IS_ERR(aspace)) {
		iommu_domain_free(domain);
		return PTR_ERR(aspace);
	}

	ret = aspace->mmu->funcs->attach(aspace->mmu, iommu_ports,
			ARRAY_SIZE(iommu_ports));
	if (ret) {
		DPU_ERROR("failed to attach iommu %d\n", ret);
		msm_gem_address_space_put(aspace);
		return ret;
	}

	dpu_kms->base.aspace = aspace;
	return 0;
}