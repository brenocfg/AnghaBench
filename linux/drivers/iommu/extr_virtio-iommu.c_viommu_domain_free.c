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
struct viommu_domain {int /*<<< orphan*/  id; TYPE_1__* viommu; } ;
struct iommu_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct viommu_domain*) ; 
 struct viommu_domain* to_viommu_domain (struct iommu_domain*) ; 
 int /*<<< orphan*/  viommu_del_mappings (struct viommu_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viommu_domain_free(struct iommu_domain *domain)
{
	struct viommu_domain *vdomain = to_viommu_domain(domain);

	iommu_put_dma_cookie(domain);

	/* Free all remaining mappings (size 2^64) */
	viommu_del_mappings(vdomain, 0, 0);

	if (vdomain->viommu)
		ida_free(&vdomain->viommu->domain_ids, vdomain->id);

	kfree(vdomain);
}