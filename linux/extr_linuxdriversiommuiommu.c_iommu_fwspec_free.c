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
struct iommu_fwspec {int /*<<< orphan*/  iommu_fwnode; } ;
struct device {struct iommu_fwspec* iommu_fwspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iommu_fwspec*) ; 

void iommu_fwspec_free(struct device *dev)
{
	struct iommu_fwspec *fwspec = dev->iommu_fwspec;

	if (fwspec) {
		fwnode_handle_put(fwspec->iommu_fwnode);
		kfree(fwspec);
		dev->iommu_fwspec = NULL;
	}
}