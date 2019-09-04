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
struct omap_iommu_arch_data {scalar_t__ iommu_dev; } ;
struct TYPE_2__ {struct omap_iommu_arch_data* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */

__attribute__((used)) static int omap_iommu_count(struct device *dev)
{
	struct omap_iommu_arch_data *arch_data = dev->archdata.iommu;
	int count = 0;

	while (arch_data->iommu_dev) {
		count++;
		arch_data++;
	}

	return count;
}