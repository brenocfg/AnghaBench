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
struct pasid_table {int dummy; } ;
struct device_domain_info {struct pasid_table* pasid_table; } ;
struct TYPE_2__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */

struct pasid_table *intel_pasid_get_table(struct device *dev)
{
	struct device_domain_info *info;

	info = dev->archdata.iommu;
	if (!info)
		return NULL;

	return info->pasid_table;
}