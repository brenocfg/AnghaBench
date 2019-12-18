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
struct iommu_domain {int dummy; } ;
struct gart_device {scalar_t__ active_devices; int /*<<< orphan*/  dom_lock; int /*<<< orphan*/ * active_domain; } ;
struct TYPE_2__ {struct iommu_domain* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 struct gart_device* gart_handle ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gart_iommu_detach_dev(struct iommu_domain *domain,
				  struct device *dev)
{
	struct gart_device *gart = gart_handle;

	spin_lock(&gart->dom_lock);

	if (dev->archdata.iommu == domain) {
		dev->archdata.iommu = NULL;

		if (--gart->active_devices == 0)
			gart->active_domain = NULL;
	}

	spin_unlock(&gart->dom_lock);
}