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
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iommu_detach_device (struct iommu_domain*,struct device*) ; 

__attribute__((used)) static int iommu_group_do_detach_device(struct device *dev, void *data)
{
	struct iommu_domain *domain = data;

	__iommu_detach_device(domain, dev);

	return 0;
}