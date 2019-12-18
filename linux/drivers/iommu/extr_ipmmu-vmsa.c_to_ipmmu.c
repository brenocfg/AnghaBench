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
struct ipmmu_vmsa_device {int dummy; } ;
struct iommu_fwspec {struct ipmmu_vmsa_device* iommu_priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 

__attribute__((used)) static struct ipmmu_vmsa_device *to_ipmmu(struct device *dev)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	return fwspec ? fwspec->iommu_priv : NULL;
}