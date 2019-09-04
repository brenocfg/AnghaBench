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
struct msm_gem_address_space {TYPE_4__* mmu; } ;
struct iommu_domain {int dummy; } ;
struct TYPE_5__ {struct msm_gem_address_space* aspace; } ;
struct dpu_kms {TYPE_1__ base; TYPE_3__* dev; } ;
struct TYPE_8__ {TYPE_2__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int (* attach ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 scalar_t__ IS_ERR (struct msm_gem_address_space*) ; 
 int PTR_ERR (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  _dpu_kms_mmu_destroy (struct dpu_kms*) ; 
 struct iommu_domain* iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_ports ; 
 struct msm_gem_address_space* msm_gem_address_space_create (int /*<<< orphan*/ ,struct iommu_domain*,char*) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dpu_kms_mmu_init(struct dpu_kms *dpu_kms)
{
	struct iommu_domain *domain;
	struct msm_gem_address_space *aspace;
	int ret;

	domain = iommu_domain_alloc(&platform_bus_type);
	if (!domain)
		return 0;

	aspace = msm_gem_address_space_create(dpu_kms->dev->dev,
			domain, "dpu1");
	if (IS_ERR(aspace)) {
		ret = PTR_ERR(aspace);
		goto fail;
	}

	dpu_kms->base.aspace = aspace;

	ret = aspace->mmu->funcs->attach(aspace->mmu, iommu_ports,
			ARRAY_SIZE(iommu_ports));
	if (ret) {
		DPU_ERROR("failed to attach iommu %d\n", ret);
		msm_gem_address_space_put(aspace);
		goto fail;
	}

	return 0;
fail:
	_dpu_kms_mmu_destroy(dpu_kms);

	return ret;
}