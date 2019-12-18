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
struct omap_iommu_domain {int /*<<< orphan*/  lock; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _omap_iommu_detach_dev (struct omap_iommu_domain*,struct device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct omap_iommu_domain* to_omap_domain (struct iommu_domain*) ; 

__attribute__((used)) static void omap_iommu_detach_dev(struct iommu_domain *domain,
				  struct device *dev)
{
	struct omap_iommu_domain *omap_domain = to_omap_domain(domain);

	spin_lock(&omap_domain->lock);
	_omap_iommu_detach_dev(omap_domain, dev);
	spin_unlock(&omap_domain->lock);
}