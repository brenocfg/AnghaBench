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
struct device {TYPE_1__* iommu_group; } ;
struct TYPE_2__ {struct iommu_domain* default_domain; } ;

/* Variables and functions */

struct iommu_domain *iommu_get_dma_domain(struct device *dev)
{
	return dev->iommu_group->default_domain;
}