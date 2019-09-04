#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_domain_info {TYPE_2__* pasid_table; } ;
struct TYPE_3__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct TYPE_4__ {int max_pasid; } ;

/* Variables and functions */

int intel_pasid_get_dev_max_id(struct device *dev)
{
	struct device_domain_info *info;

	info = dev->archdata.iommu;
	if (!info || !info->pasid_table)
		return 0;

	return info->pasid_table->max_pasid;
}