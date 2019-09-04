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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach_dev ) (struct iommu_domain*,struct device*) ;scalar_t__ (* is_attach_deferred ) (struct iommu_domain*,struct device*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct iommu_domain*,struct device*) ; 
 int /*<<< orphan*/  stub2 (struct iommu_domain*,struct device*) ; 
 int /*<<< orphan*/  trace_detach_device_from_domain (struct device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __iommu_detach_device(struct iommu_domain *domain,
				  struct device *dev)
{
	if ((domain->ops->is_attach_deferred != NULL) &&
	    domain->ops->is_attach_deferred(domain, dev))
		return;

	if (unlikely(domain->ops->detach_dev == NULL))
		return;

	domain->ops->detach_dev(domain, dev);
	trace_detach_device_from_domain(dev);
}