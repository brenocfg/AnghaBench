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
struct msm_mmu {int dummy; } ;
struct msm_iommu {struct msm_mmu base; struct iommu_domain* domain; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_mmu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  funcs ; 
 int /*<<< orphan*/  iommu_set_fault_handler (struct iommu_domain*,int /*<<< orphan*/ ,struct msm_iommu*) ; 
 struct msm_iommu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_fault_handler ; 
 int /*<<< orphan*/  msm_mmu_init (struct msm_mmu*,struct device*,int /*<<< orphan*/ *) ; 

struct msm_mmu *msm_iommu_new(struct device *dev, struct iommu_domain *domain)
{
	struct msm_iommu *iommu;

	iommu = kzalloc(sizeof(*iommu), GFP_KERNEL);
	if (!iommu)
		return ERR_PTR(-ENOMEM);

	iommu->domain = domain;
	msm_mmu_init(&iommu->base, dev, &funcs);
	iommu_set_fault_handler(domain, msm_fault_handler, iommu);

	return &iommu->base;
}