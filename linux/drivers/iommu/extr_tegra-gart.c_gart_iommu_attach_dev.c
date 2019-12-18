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
struct gart_device {int /*<<< orphan*/  dom_lock; int /*<<< orphan*/  active_devices; struct iommu_domain* active_domain; } ;
struct TYPE_2__ {struct iommu_domain* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int EBUSY ; 
 struct gart_device* gart_handle ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gart_iommu_attach_dev(struct iommu_domain *domain,
				 struct device *dev)
{
	struct gart_device *gart = gart_handle;
	int ret = 0;

	spin_lock(&gart->dom_lock);

	if (gart->active_domain && gart->active_domain != domain) {
		ret = -EBUSY;
	} else if (dev->archdata.iommu != domain) {
		dev->archdata.iommu = domain;
		gart->active_domain = domain;
		gart->active_devices++;
	}

	spin_unlock(&gart->dom_lock);

	return ret;
}