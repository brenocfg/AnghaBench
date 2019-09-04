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
struct rk_iommudata {struct rk_iommu* iommu; } ;
struct rk_iommu {int dummy; } ;
struct TYPE_2__ {struct rk_iommudata* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */

__attribute__((used)) static struct rk_iommu *rk_iommu_from_dev(struct device *dev)
{
	struct rk_iommudata *data = dev->archdata.iommu;

	return data ? data->iommu : NULL;
}