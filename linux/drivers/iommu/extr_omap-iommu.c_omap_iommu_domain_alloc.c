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
struct TYPE_2__ {unsigned long long aperture_end; int force_aperture; scalar_t__ aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct omap_iommu_domain {struct iommu_domain domain; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 struct omap_iommu_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iommu_domain *omap_iommu_domain_alloc(unsigned type)
{
	struct omap_iommu_domain *omap_domain;

	if (type != IOMMU_DOMAIN_UNMANAGED)
		return NULL;

	omap_domain = kzalloc(sizeof(*omap_domain), GFP_KERNEL);
	if (!omap_domain)
		return NULL;

	spin_lock_init(&omap_domain->lock);

	omap_domain->domain.geometry.aperture_start = 0;
	omap_domain->domain.geometry.aperture_end   = (1ULL << 32) - 1;
	omap_domain->domain.geometry.force_aperture = true;

	return &omap_domain->domain;
}