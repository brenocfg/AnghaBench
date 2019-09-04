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
typedef  int /*<<< orphan*/  u32 ;
struct iommu_domain_geometry {int dummy; } ;
struct iommu_domain {unsigned long pgsize_bitmap; TYPE_1__* ops; struct iommu_domain_geometry geometry; } ;
typedef  enum iommu_attr { ____Placeholder_iommu_attr } iommu_attr ;
struct TYPE_2__ {int (* domain_get_attr ) (struct iommu_domain*,int,void*) ;int /*<<< orphan*/  (* domain_get_windows ) (struct iommu_domain*) ;} ;

/* Variables and functions */
#define  DOMAIN_ATTR_GEOMETRY 130 
#define  DOMAIN_ATTR_PAGING 129 
#define  DOMAIN_ATTR_WINDOWS 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  stub1 (struct iommu_domain*) ; 
 int stub2 (struct iommu_domain*,int,void*) ; 

int iommu_domain_get_attr(struct iommu_domain *domain,
			  enum iommu_attr attr, void *data)
{
	struct iommu_domain_geometry *geometry;
	bool *paging;
	int ret = 0;
	u32 *count;

	switch (attr) {
	case DOMAIN_ATTR_GEOMETRY:
		geometry  = data;
		*geometry = domain->geometry;

		break;
	case DOMAIN_ATTR_PAGING:
		paging  = data;
		*paging = (domain->pgsize_bitmap != 0UL);
		break;
	case DOMAIN_ATTR_WINDOWS:
		count = data;

		if (domain->ops->domain_get_windows != NULL)
			*count = domain->ops->domain_get_windows(domain);
		else
			ret = -ENODEV;

		break;
	default:
		if (!domain->ops->domain_get_attr)
			return -EINVAL;

		ret = domain->ops->domain_get_attr(domain, attr, data);
	}

	return ret;
}