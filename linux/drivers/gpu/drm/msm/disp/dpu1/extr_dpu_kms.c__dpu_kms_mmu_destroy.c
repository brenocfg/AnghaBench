#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_mmu {TYPE_1__* funcs; } ;
struct TYPE_5__ {TYPE_3__* aspace; } ;
struct dpu_kms {TYPE_2__ base; } ;
struct TYPE_6__ {struct msm_mmu* mmu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* detach ) (struct msm_mmu*,char const**,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__) ; 
 scalar_t__ iommu_ports ; 
 int /*<<< orphan*/  msm_gem_address_space_put (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct msm_mmu*,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dpu_kms_mmu_destroy(struct dpu_kms *dpu_kms)
{
	struct msm_mmu *mmu;

	if (!dpu_kms->base.aspace)
		return;

	mmu = dpu_kms->base.aspace->mmu;

	mmu->funcs->detach(mmu, (const char **)iommu_ports,
			ARRAY_SIZE(iommu_ports));
	msm_gem_address_space_put(dpu_kms->base.aspace);

	dpu_kms->base.aspace = NULL;
}