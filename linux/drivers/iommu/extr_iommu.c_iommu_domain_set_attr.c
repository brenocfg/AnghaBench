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
struct iommu_domain {TYPE_1__* ops; } ;
typedef  enum iommu_attr { ____Placeholder_iommu_attr } iommu_attr ;
struct TYPE_2__ {int (* domain_set_attr ) (struct iommu_domain*,int,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct iommu_domain*,int,void*) ; 

int iommu_domain_set_attr(struct iommu_domain *domain,
			  enum iommu_attr attr, void *data)
{
	int ret = 0;

	switch (attr) {
	default:
		if (domain->ops->domain_set_attr == NULL)
			return -EINVAL;

		ret = domain->ops->domain_set_attr(domain, attr, data);
	}

	return ret;
}