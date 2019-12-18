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
struct iommu_domain {unsigned int type; int /*<<< orphan*/  pgsize_bitmap; TYPE_1__* ops; } ;
struct bus_type {TYPE_1__* iommu_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  pgsize_bitmap; struct iommu_domain* (* domain_alloc ) (unsigned int) ;} ;

/* Variables and functions */
 struct iommu_domain* stub1 (unsigned int) ; 

__attribute__((used)) static struct iommu_domain *__iommu_domain_alloc(struct bus_type *bus,
						 unsigned type)
{
	struct iommu_domain *domain;

	if (bus == NULL || bus->iommu_ops == NULL)
		return NULL;

	domain = bus->iommu_ops->domain_alloc(type);
	if (!domain)
		return NULL;

	domain->ops  = bus->iommu_ops;
	domain->type = type;
	/* Assume all sizes by default; the driver may override this later */
	domain->pgsize_bitmap  = bus->iommu_ops->pgsize_bitmap;

	return domain;
}