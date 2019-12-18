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
struct viommu_domain {unsigned int id; int /*<<< orphan*/  map_flags; struct viommu_dev* viommu; } ;
struct viommu_dev {int /*<<< orphan*/  last_domain; int /*<<< orphan*/  first_domain; int /*<<< orphan*/  domain_ids; int /*<<< orphan*/  geometry; int /*<<< orphan*/  pgsize_bitmap; int /*<<< orphan*/  map_flags; } ;
struct iommu_domain {int /*<<< orphan*/  geometry; int /*<<< orphan*/  pgsize_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_alloc_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct viommu_domain* to_viommu_domain (struct iommu_domain*) ; 

__attribute__((used)) static int viommu_domain_finalise(struct viommu_dev *viommu,
				  struct iommu_domain *domain)
{
	int ret;
	struct viommu_domain *vdomain = to_viommu_domain(domain);

	vdomain->viommu		= viommu;
	vdomain->map_flags	= viommu->map_flags;

	domain->pgsize_bitmap	= viommu->pgsize_bitmap;
	domain->geometry	= viommu->geometry;

	ret = ida_alloc_range(&viommu->domain_ids, viommu->first_domain,
			      viommu->last_domain, GFP_KERNEL);
	if (ret >= 0)
		vdomain->id = (unsigned int)ret;

	return ret > 0 ? 0 : ret;
}