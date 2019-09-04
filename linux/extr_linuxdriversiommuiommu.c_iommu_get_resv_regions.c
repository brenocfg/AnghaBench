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
struct list_head {int dummy; } ;
struct iommu_ops {int /*<<< orphan*/  (* get_resv_regions ) (struct device*,struct list_head*) ;} ;
struct device {TYPE_1__* bus; } ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct device*,struct list_head*) ; 

void iommu_get_resv_regions(struct device *dev, struct list_head *list)
{
	const struct iommu_ops *ops = dev->bus->iommu_ops;

	if (ops && ops->get_resv_regions)
		ops->get_resv_regions(dev, list);
}