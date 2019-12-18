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
struct ipmmu_vmsa_domain {int dummy; } ;
struct iommu_fwspec {unsigned int num_ids; int /*<<< orphan*/ * ids; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  ipmmu_utlb_disable (struct ipmmu_vmsa_domain*,int /*<<< orphan*/ ) ; 
 struct ipmmu_vmsa_domain* to_vmsa_domain (struct iommu_domain*) ; 

__attribute__((used)) static void ipmmu_detach_device(struct iommu_domain *io_domain,
				struct device *dev)
{
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	struct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);
	unsigned int i;

	for (i = 0; i < fwspec->num_ids; ++i)
		ipmmu_utlb_disable(domain, fwspec->ids[i]);

	/*
	 * TODO: Optimize by disabling the context when no device is attached.
	 */
}